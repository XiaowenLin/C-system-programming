#include <stdlib.h>
#include <stdio.h>
#include "parsort.h"
#include <time.h>
/* return an array of random numbers */
void shuffle(int *array, int size){
    int i;
    srand(time(NULL));
    for (i = 0; i < size; i++){
        array[i] = rand()%1000;
    }
}

void prt(int *array, int size){
    int i;
    for (i= 0; i < size; i++){
        printf("%d ", array[i]);
    }
    puts("");
}

int main(int argc, char *argv[]){
    char * count = argv[1];
    int num = atoi(count);
    int arr0[num];
    int *p = arr0;
    shuffle(p, num);
//    prt(arr0, num);
    //int arr[] = {10, 49, 9, 34, 32, 37, 37, 48, 45, 19, 5, 31, 20, 19, 29, 22, 45, 30, 40, 31, 35, 8, 36, 39, 14, 18, 19};
    // int arr[] =  {10, 49, 9, 34, 32, 37, 37, 48, 45, 19};
	data_t mydata;
	mydata.data_size = num;
	mydata.data = arr0;
	mydata.thread_count = 1;
    puts("start sort");
	data_t thedata = parsort(mydata);
    prt(arr0, num);
    return 0;
}
