#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"

/*
 * You are responsible for making this function thread_safe
 * This function initializes the merge_sort scheduler
 */
void scheduler_init(scheduler_t* scheduler, int thread_count, int* data, int data_size){
  if(thread_count > data_size){
    thread_count = data_size;
  }

  int qsort_num_per_task = data_size/thread_count;
  int last_task_count = qsort_num_per_task;
  if(data_size%thread_count!=0)
    last_task_count = qsort_num_per_task + data_size%thread_count;

  scheduler->base = (void*)data;
  scheduler->thread_count = thread_count;
  scheduler->last_task_count = last_task_count;
  scheduler->qsort_num_per_task = qsort_num_per_task;
  scheduler->Nthread = 0;	
  scheduler->task_id_count = 1;	
  scheduler->data = data;
  scheduler->data_size = data_size;
  scheduler->task_id_loc = malloc(sizeof(int)*thread_count*thread_count*10);
  scheduler->meta_arr = malloc(sizeof(meta_t*)*thread_count);
  int i=0;
  for(i=0; i<thread_count; i++){
    scheduler->meta_arr[i] = malloc(sizeof(meta_t)*thread_count);
    int j;
    for(j=0; j<thread_count; j++)
      scheduler->meta_arr[i][j].task_a = -1;
  }
  scheduler->iterCount = malloc(sizeof(int)*thread_count*thread_count*10);
  scheduler->currIter = malloc(sizeof(int)*thread_count*thread_count*10);
  int iterOld = thread_count;
  int idx = 1;
  scheduler->iterCount[0] = iterOld;
  while(iterOld>0){
    int iter = iterOld/2;
    if(iterOld%2!=0 && iterOld!=1)
      iter++;
    scheduler->iterCount[idx] = iter;
    idx++;
    iterOld = iter;
  }	
}

/*
 * You are responsible for making this function thread_safe
 * This function is called to retrieve task from the scheduler
 * thread_id represent the id of thread, this id starts counting from 0
 * iteration represent the ith iteration of the sort/merge process, starts counting from 1
 * If the function returns a task_type to exit, the sorting thread which calls this function will exit 
 */
task_t scheduler_get_qsort_task(scheduler_t* scheduler){
  task_t ret_task;
  memset(&ret_task,0x0,sizeof(task_t));
  if(scheduler->Nthread >= scheduler->thread_count)
    ret_task.type = EXIT;
  else{
    ret_task.type = QUICKSORT;
    ret_task.base = scheduler->data;
    ret_task.startIdx = scheduler->Nthread*scheduler->qsort_num_per_task;
    if(scheduler->Nthread==scheduler->thread_count-1)
      ret_task.endIdx = ret_task.startIdx + scheduler->last_task_count - 1;
    else
      ret_task.endIdx = ret_task.startIdx + scheduler->qsort_num_per_task - 1; 
    ret_task.task_id = scheduler->task_id_count;
    scheduler->task_id_count++;
    scheduler->currIter[ret_task.task_id] = 1;	
    //register_qsort(scheduler->task_id_count, ret_task.endIdxA - ret_task.startIdxA +1);
    //		printf("TASK ID: %d QSORT %d elements\n", scheduler->task_id_count, ret_task.endIdxA - ret_task.startIdxA +1);	
  }	
  scheduler->task_id_loc[ret_task.task_id] = scheduler->Nthread/2;
  scheduler->Nthread++;
  return ret_task;
}

/*
 * You are responsible for making this function thread_safe
 * Informing the scheduler that ith thread is finished processing its task 
 */
task_t scheduler_finish_and_get_new_task(scheduler_t* scheduler, int old_task_id){
  task_t ret_task;
  memset(&ret_task,0x0,sizeof(task_t));
  int loc = scheduler->task_id_loc[old_task_id];
  int iter = scheduler->currIter[old_task_id];
  if(scheduler->iterCount[iter]==0){
    ret_task.type = EXIT;
    return ret_task;
  }
  else if(scheduler->meta_arr[iter][loc].task_a==-1){
    //PASS
    if(scheduler->iterCount[iter-1]%2!=0 && loc==scheduler->iterCount[iter]-1){
      ret_task.pass_id = old_task_id;
      ret_task.type = PASS;
      //register_pass(scheduler->task_id_count, old_task.task_id);
      //			printf("TASK ID: %d PASS(%d)\n", scheduler->task_id_count, old_task.task_id);	
    }
    //EXIT
    else {
      scheduler->meta_arr[iter][loc].task_a = old_task_id;		
      ret_task.type = EXIT;
      return ret_task;
    }
  }
  else{
    //NORMAL	
    ret_task.base = scheduler->base;
    ret_task.merge_id_a = scheduler->meta_arr[iter][loc].task_a;
    ret_task.merge_id_b = old_task_id;
    ret_task.type = MERGE;
    //register_merge(scheduler->task_id_count, scheduler->meta_arr[iter][loc].task_A.task_id, old_task.task_id, AEnd-AStart+1, oldEnd-oldStart+1);
    //		printf("TASK ID: %d MERGE(%d,%d): merge %d elements and %d elements\n", scheduler->task_id_count, scheduler->meta_arr[iter][loc].task_A.task_id, old_task.task_id, AEnd-AStart+1, oldEnd-oldStart+1);	
  }
  ret_task.task_id = scheduler->task_id_count;
  scheduler->task_id_count++;
  scheduler->task_id_loc[ret_task.task_id] = loc/2;
  scheduler->currIter[ret_task.task_id] = scheduler->currIter[old_task_id] + 1;
  return ret_task;
}

/*
 * You are responsible for making this function thread_safe
 * Destroys the shared mergesort scheduler
 */
void scheduler_destroy(scheduler_t* scheduler){
  //Your Implementation Goes here...
  free(scheduler->task_id_loc);
  free(scheduler->iterCount);
  free(scheduler->currIter);
  int i;
  for(i=0; i<scheduler->thread_count; i++)
    free(scheduler->meta_arr[i]);
  free(scheduler->meta_arr);
}
