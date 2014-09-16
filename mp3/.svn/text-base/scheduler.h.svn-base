typedef enum {QUICKSORT, MERGE, PASS, EXIT} taskType;

/**
 * If taskType is QUICKSORT:
 *	base, startIdx, endIdx, task_id and type are valid fields
 * If taskType is EXIT:
 *	type is the only valid field
 * If taskType is PASS:
 * 	base, type, task_id and pass_id are valid fields
 * If taskType is MERGE:
 *	type, task_id, merge_id_a, merge_id_b are valid fields
 */
typedef struct task_t_{
	void* base;
	int startIdx;
	int endIdx;
	taskType type;
	int task_id;
	int pass_id;
	int merge_id_a;
	int merge_id_b;
} task_t;



//You do not need to worry about anything starting from here:
typedef struct meta_t_{
	int task_a;
	int task_b;
}meta_t;

typedef struct scheduler_t_{
	int* task_id_loc;
	int* currIter;
	int* iterCount;
	meta_t** meta_arr;
	int Nthread;
	int qsort_num_per_task;
	int last_task_count;
	int thread_count;
	int* data;
	int data_size;
	int task_id_count;
	void* base;
} scheduler_t;

void scheduler_init(scheduler_t* scheduler, int thread_count, int* data, int data_size);
task_t scheduler_get_qsort_task(scheduler_t* scheduler);
task_t scheduler_finish_and_get_new_task(scheduler_t* scheduler, int old_task_id);
void scheduler_destroy(scheduler_t* schduler);
