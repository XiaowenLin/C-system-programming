#ifndef _TRIE_H
#define _TRIE_H

#include "../lab0/libqueue.h"

//extern int curN;
typedef struct trieNode{
	char *key;
	char *str;
	int count;
	struct trieNode *child;
	struct trieNode *next;
}trieNode_t;

typedef struct trie{
	trieNode_t *root;
} trie_t;

trieNode_t *trieNode_new(char *c, char *str); /* PASS: create a new node */ 
void trie_init(trie_t *t); /* PASS */ 
trieNode_t *trieNode_list(const char *str, const char *ori); /* PASS: create a list of nodes */
/* PASS: 
given a non-null char, compare all non-null nodes at this level, 
return pointer to the match or NULL */
trieNode_t *trie_levelMatch(trieNode_t *t, const char *c); /* PASS */
void trie_destroyHelper(trieNode_t *t); /* PASS */
void trie_destroy(trie_t *t); /* PASS */
void trie_addHelper(trieNode_t *t, const char *strconst, const char *ori); /* PASS */
void trie_add(trie_t *t, const char *str); /* PASS */
int trie_sum(trieNode_t *t); /* PASS */ 
int trie_freq_countHelper(trieNode_t *t, const char *prefix); /* PASS */ 
int trie_freq_count(trie_t *t, const char *prefix); /* PASS */ 
void trie_allStr(queue_t *q, trieNode_t *t); /* PASS */
queue_t *trie_all_matchesHelper(trieNode_t *t, const char *prefix); /* PASS */
queue_t *trie_all_matches(trie_t *t, const char *prefix); /* PASS */
void trie_longestSub(trieNode_t *t, trieNode_t* lnode, int flag); /* PASS */
char *trie_most_freq_matchHelper(trieNode_t *t, const char *prefix); /* PASS */
char *trie_most_freq_match(trie_t *t, const char *prefix); /* PASS */

char *trie_longest_prefixHelper(trieNode_t *t, const char *str); /* PASS */
char *trie_longest_prefix(trie_t *t, const char *str); /* PASS */

void trie_printHelper(trieNode_t *t); /* PASS */
void trie_print(trie_t *t); /* PASS */

#endif
