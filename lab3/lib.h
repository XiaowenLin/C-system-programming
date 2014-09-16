typedef struct {
  int *arr;
  size_t size;
  int min;
  int max;
} arr_t;

arr_t *read_num_file(char *file_name);
void single_sort(int *arr,size_t size,int thread_idx);
