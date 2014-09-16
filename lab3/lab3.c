#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lib.h"

typedef struct{
	int *arr;
	size_t size;
	int thread_idx;
}sortparam;

int *getbin(arr_t *nf, size_t *bin_size, size_t i, size_t num_buckets) {
	// [min+i*bucket_size, min+(i+1)*bucket_size)
	size_t dif = (size_t)nf->max - (size_t)nf->min;
	size_t bucket_size = dif / num_buckets;
	size_t lb = nf->min + i*bucket_size;
	size_t rb = nf->min + (i+1)*bucket_size;
	// [min+(num_buckets-1)*bucket_size, max]
	if (i + 1 == num_buckets) {
		lb = (size_t)nf->min+(num_buckets-1)*bucket_size;
		rb = nf->max + 1;
	}
	/* add num into bin within boundary, and count */
	size_t j;
	size_t count = 0;
	size_t m              = nf->size;
	for (j = 0; j < m; j++) {
		if (lb <= nf->arr[j] && rb > nf->arr[j]) {
			count++;
		}
	}
	
	*bin_size = count;
	int *ret = (int *)malloc(count*sizeof(int));
	count = 0;
	for (j = 0; j < m; j++) {
		if (lb <= nf->arr[j] && rb > nf->arr[j]) {
			ret[count] = nf->arr[j];
			count++;
		}
	}
	return ret;
}

void *sort_wrapper(void *ptr)
{
	sortparam *mptr = (sortparam *)ptr;
	single_sort(mptr->arr, mptr->size, mptr->thread_idx);
	pthread_exit(NULL);
}

void wrt(size_t num_buckets, pthread_t *threads, char *filename, size_t *bin_ss, int **bins) {
	size_t i;
	for (i = 0; i < num_buckets; i++)
       pthread_join(threads[i], NULL);
       
	FILE *sorted = fopen(filename, "w");
	size_t j;
	for (i = 0; i < num_buckets; i++) {
		for (j = 0; j < bin_ss[i]; j++) {
			fprintf(sorted, "%d\n", bins[i][j]);
		}
		
		/* --release bin */
		free(bins[i]);
	}
	fclose(sorted);
}

int main(int argc,char **argv){
	arr_t *nf_arr = read_num_file(argv[1]);
	size_t num_buckets = (size_t)atoi(argv[2]);
	int *bins[num_buckets];
	size_t bin_ss[num_buckets];
	sortparam s_param[num_buckets];
	
	size_t i;
	pthread_t threads[num_buckets];
	for (i = 0; i < num_buckets; i++) {/* loop */
		/* --create a bin */
		bins[i] = getbin(nf_arr, bin_ss+i, i, num_buckets);
		
		/* --create thread; use thrd to sort numbers in this bin */
		s_param[i].arr = bins[i];
		s_param[i].size = bin_ss[i];
		s_param[i].thread_idx = i;
		pthread_create(&threads[i], NULL, sort_wrapper, (void *)&s_param[i]); 
	}
	
	/* wait until all thrds finish */
	wrt(num_buckets, threads, "sorted.txt", bin_ss, bins);
	
	/* free and exit */
	free(nf_arr->arr);
	free(nf_arr);
  pthread_exit(NULL);
  return 0;
}
