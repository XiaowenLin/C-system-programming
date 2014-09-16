#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "libqueue.h"
#include "debug.h"

int main(){
  queue_t test_queue;
  queue_init(&test_queue);
  assert(queue_size(&test_queue)==0);

  char str[20]="node";

  queue_enqueue(&test_queue,str);
  assert(queue_size(&test_queue)==1);
  queue_destroy(&test_queue,0);
  puts("Passed all tests (you should add more tests yourself)");
  return 0;
}
