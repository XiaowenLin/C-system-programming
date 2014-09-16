#include "parsort.h"
#include "scheduler.h"
#include "register.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/* unit to keep id->startIdx, endIdx */
typedef struct _hsh {
   int startIdx;
   int endIdx; 
}hsh;

/* mix schedule pointer and hash table pointer */
typedef struct _mix {
    scheduler_t *sch;
    hsh *hsh;
}mix;

/* pointer to base */
int *base;

/* mutex schedule, register lock */
pthread_mutex_t mutexsch;
pthread_mutex_t mutexreg;

/* print all */
void prt_ar(int s, int e){
    int i;
    for (i=s;i<e+1;i++)
        printf("%d ", base[i]);
    puts("");
}

/* [qsort] compare function */
int cmp(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}

/* [qsort] copy */
void cpy(int *tmp, int n, int start, int *array){
    int i;
    for (i = 0; i < n; i++)
        tmp[i] = array[start + i];
}

/* [qsort] replace */
void replace(int *tmp, int n, int start){
    int i;
    for (i = 0; i < n; i++){
        base[start + i] = tmp[i];
    }
}

/* [qsort] wrapper */
void sort(task_t *task, hsh *tb)
{
    //puts("[qsort]");
    /* udpate hash table */
    tb[task->task_id].startIdx = task->startIdx;
    tb[task->task_id].endIdx = task->endIdx;
    /* quick sort */
    size_t nitems = task->endIdx - task->startIdx + 1;
    size_t size = sizeof(int);
    int tmp[nitems];
    cpy(tmp, nitems, task->startIdx, base);
    qsort(tmp, nitems, size, cmp);
    replace(tmp, nitems, task->startIdx);
    /* register */
    pthread_mutex_lock(&mutexreg);
    register_qsort(task->task_id, (int)nitems);
    //prt_ar(task->startIdx, task->endIdx);
    pthread_mutex_unlock(&mutexreg);
}

/* [pass] */
void pass(task_t *task, hsh *tb)
{
    /* udpate hash table */
    tb[task->task_id].startIdx = tb[task->pass_id].startIdx;
    tb[task->task_id].endIdx = tb[task->pass_id].endIdx;
    /* register */
    pthread_mutex_lock(&mutexreg);
    register_pass(task->task_id, task->pass_id);
    pthread_mutex_unlock(&mutexreg);
}

/* [merge] swap */
void swap(int ls, int rs){
    int tmp = base[ls];
    base[ls] = base[rs];
    base[rs] = tmp;
}

/* [merge] bubble */
void bubble(int s, int e){
    /* cmp elt with the next, until the end */
    int i = s;
    while (i < e){
        if (base[i] > base[i+1]){
            swap(i, i+1);    
            i++;
        }
        else break;
    }
}

/* [merge] helper */
void merge_helper(int ls, int rs, int re){
    while (base[ls] <= base[rs] && ls < rs){
        ls++;
    }
    //printf("ls=%d >= rs=%d\n", ls, rs);
    if (ls >= rs) return;
    /* swap ls and rs */
    //printf("swap %d and %d\n", base[ls], base[rs]);
    swap(ls, rs);
    /* bubble the elts */
    bubble(ls, rs-1);
    bubble(rs, re);
    /* call merge_helper */
    merge_helper(ls, rs, re);
}

/* [merge] */
void merge(task_t *task, hsh *tb)
{
    int ls = tb[task->merge_id_a].startIdx;
    int rs = tb[task->merge_id_b].startIdx;
    int le = tb[task->merge_id_a].endIdx;
    int re = tb[task->merge_id_b].endIdx;
    /* update hash table */
    int startIdx = ls < rs ? ls : rs;
    int midIdx =  ls < rs ? rs : ls;
    int endIdx = le > re ? le : re;
    tb[task->task_id].startIdx = startIdx;
    tb[task->task_id].endIdx = endIdx;
    /* merge the array */
//    sleep(1);
    merge_helper(startIdx, midIdx, endIdx);
    /* register */
    int size_a = tb[task->merge_id_a].endIdx - tb[task->merge_id_a].startIdx + 1;
    int size_b = tb[task->merge_id_b].endIdx - tb[task->merge_id_b].startIdx + 1;
    pthread_mutex_lock(&mutexreg);
	register_merge(task->task_id, task->merge_id_a, task->merge_id_b, size_a, size_b);
    //prt_ar(startIdx, endIdx);
    pthread_mutex_unlock(&mutexreg);
}

/* [merge_sort] one thread */
void *merge_sort(void *ptr){
    /* get init task */
    mix *mptr = (mix *)ptr;
    pthread_mutex_lock (&mutexsch);
    task_t single_task = scheduler_get_qsort_task(mptr->sch);
    pthread_mutex_unlock (&mutexsch);
    //puts("befor eloop");
    while(1){
        switch(single_task.type)
        {
            case QUICKSORT:
                sort(&single_task, mptr->hsh);
                break;
            case PASS:
                pass(&single_task, mptr->hsh);
      			break;
            case MERGE:
                merge(&single_task, mptr->hsh);
                break;
            case EXIT:
                pthread_exit(NULL);
                break;
            default:
           		break;
        }
        /* update task */
        pthread_mutex_lock(&mutexsch);
        single_task = scheduler_finish_and_get_new_task(mptr->sch, single_task.task_id);
        pthread_mutex_unlock(&mutexsch);
    }
}

/* [parsort] */
data_t parsort(data_t input){
    /* init scheduler */
    scheduler_t scheduler;
    scheduler_init(&scheduler, input.thread_count, input.data, input.data_size);
    /* init array of hashing */
    //puts("init array of hashing");
    hsh htb[input.thread_count * 3];
    /* init base */
    //puts("init base");
    base = input.data;
    /* declare threads */
    //puts("make threads");
    pthread_t thrds[input.thread_count];
    /* bind sch and htb */
    mix ptr;
    ptr.sch = &scheduler;
    ptr.hsh = htb;
    /* create count # of threads once */
    int i;
    for (i = 0; i < input.thread_count; i++){
        pthread_create(&thrds[i], NULL, merge_sort, (void*)&ptr);
    }
    /* join threads once */
    for (i = 0; i < input.thread_count; i++)
        pthread_join(thrds[i], NULL);
    /* destroy scheduler */
    scheduler_destroy(&scheduler);
    return input;
}
