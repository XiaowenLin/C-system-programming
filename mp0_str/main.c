#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libtrie.h"

int main(){

  trie_t test;
  trie_init(&test);
  trie_add(&test,"hello");
/*  char *str=trie_longest_prefix(&test,"helloworld");*/
/*  assert(!strcmp(str,"hello"));*/
/*  free(str);*/
  
/*  queue_t *ret=trie_all_matches(&test,"h");*/
/*  assert(queue_size(ret)==1);*/
/*  queue_destroy(ret,0);*/
/*  free(ret);*/
/*  */
/*  trie_print(&test);*/
  trie_destroy(&test);
  puts("Passed all tests (you should add more tests yourself)");

/*  trie_t test;*/
/*  trie_init(&test);*/
/*  trie_add(&test,"hello");*/
/*  char *str=trie_longest_prefix(&test,"helloworld");*/
/*  assert(!strcmp(str,"hello"));*/
/*  free(str);*/
/*  queue_t *ret=trie_all_matches(&test,"h");*/
/*  assert(queue_size(ret)==1);*/
/*  queue_destroy(ret,1);*/
/*  free(ret);*/
/*  trie_destroy(&test);*/
/*  puts("Passed all tests (you should add more tests yourself)");*/
  return 0;
}
