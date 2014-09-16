#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libtrie.h"

int main(){

/*  trie_print(&test);*/
/*  trie_destroy(&test);*/
/*  puts("Passed all tests (you should add more tests yourself)");*/

  trie_t test;
  trie_init(&test);
  trie_add(&test,"hello");
  char *str=trie_longest_prefix(&test,"helloworld");
  assert(!strcmp(str,"hello"));
  free(str);
  trie_add(&test,"hellor");
  trie_add(&test,"hellws");
  trie_add(&test,"fellws");
  queue_t *ret=trie_all_matches(&test,"h");
  puts("$$$$$$$$$$$$$$$$$$$$$");
  queue_print(ret);
  assert(queue_size(ret)==3);
  queue_destroy(ret,1);
  free(ret);
  
  queue_t *ret1=trie_all_matches(&test,"");
  puts("$$$$$$$$$$$$$$$$$$$$$");
  queue_print(ret1);
  queue_destroy(ret1,1);
  free(ret1);
  trie_add(&test,"fefsdfsdllws");
  trie_add(&test,"hell");
    trie_add(&test, "hell");
  trie_print(&test);
  
  str=trie_longest_prefix(&test,"hellore");
  assert(!strcmp(str,"hellor"));
  free(str);
  
  char *str1= trie_most_freq_match(&test, "f");
  puts("most freq match________________________");
  printf("%s", str1);
  free(str1);
  
  int n = trie_freq_count(&test, "h");
  printf("most freq count__________________%d__________________", n);
  
  trie_destroy(&test);
  puts("Passed all tests (you should add more tests yourself)");



/*  trie_t test;*/
/*  trie_init(&test);*/
/*  trie_add(&test,"hello");*/
/*  trie_add(&test,"hello");*/
/*  trie_add(&test,"hello");*/
/*  trie_add(&test,"hdfello");*/
/*  trie_add(&test,"ft4rhello");*/
/*  trie_print(&test);*/
/*  puts("YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY");*/
/*  char *str=trie_longest_prefix(&test,"helloworld");*/
/*   trie_print(&test);*/
/*  assert(!strcmp(str,"hello"));*/
/*  free(str);*/
/*   trie_print(&test);*/

/*  queue_t *ret=trie_all_matches(&test,"h");*/
/*  assert(queue_size(ret)==2);*/
/*  queue_destroy(ret,0);*/
/*  free(ret);*/
/*  */
/*   trie_add(&test,"ffffffo");*/
/*  trie_add(&test,"ft4rhello");*/
/*  trie_print(&test);*/
/*  puts("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");*/
/*  queue_t *ret1=trie_all_matches(&test,"h");*/
/*  printf("queue size %lu\n", queue_size(ret1));*/
/*  queue_print(ret1);*/
/*  puts("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ");*/
/*  queue_t *ret2=trie_all_matches(&test,"f");*/
/*  printf("queue size %lu\n", queue_size(ret2));*/
/*  queue_print(ret2);*/
/*  assert(queue_size(ret1)==2);*/
/*  queue_destroy(ret1,0);*/
/*  free(ret1);*/
/*  */
/*  trie_print(&test);*/
/*  trie_destroy(&test);*/
/*  puts("Passed all tests (you should add more tests yourself)");*/

/*  trie_t test;*/
/*  trie_init(&test);*/
/*  trie_add(&test,"hello");*/
/*  char *str=trie_longest_prefix(&test,"helloworld");*/
/*  assert(!strcmp(str,"hello"));*/
/*  free(str);*/
/*  trie_add(&test,"hello");*/
/*  trie_add(&test,"hellws");*/
/*  trie_add(&test,"fellws");*/
/*  queue_t *ret=trie_all_matches(&test,"h");*/
/*  puts("$$$$$$$$$$$$$$$$$$$$$");*/
/*  queue_print(ret);*/
/*  assert(queue_size(ret)==2);*/
/*  queue_destroy(ret,1);*/
/*  free(ret);*/
/*  */
/*  queue_t *ret1=trie_all_matches(&test,"");*/
/*  puts("$$$$$$$$$$$$$$$$$$$$$");*/
/*  queue_print(ret1);*/
/*  queue_destroy(ret1,1);*/
/*  free(ret1);*/
/*  trie_add(&test,"fefsdfsdllws");*/
/*  trie_destroy(&test);*/
/*  puts("Passed all tests (you should add more tests yourself)");*/

  trie_t test;
  trie_init(&test);
  trie_add(&test,"hello");
  char *str=trie_longest_prefix(&test,"helloworld");
  assert(!strcmp(str,"hello"));
  free(str);
  queue_t *ret=trie_all_matches(&test,"h");
  assert(queue_size(ret)==1);
  queue_destroy(ret,1);
  free(ret);
  trie_destroy(&test);
  puts("Passed all tests (you should add more tests yourself)");
  return 0;
}
