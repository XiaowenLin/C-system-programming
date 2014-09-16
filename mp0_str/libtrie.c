#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libtrie.h"
#include "../lab0/libqueue.h"

/*int curN = 0;*/

/* Given a pointer to a dynm char, and a pointer to dynm string
create a node */
trieNode_t *trieNode_new(char *c, char *pref)
{
/*	curN++;*/
	trieNode_t *node;
	node = (trieNode_t *) malloc(sizeof(trieNode_t));
	node->key = c;
	node->str = pref;
	node->count = 0;
	node->child = NULL;
	node->next = NULL;
/*	if (*node->key != '\0') printf("trieNode_new(%s)---curN=%d\n", node->str, curN);*/
/*	else printf("trieNode_new #---curN=%d\n", curN);*/
	return node;
	
	
};

/* Given an allocated trie header struct, 
create new \0 node, with root pointing at it */
void trie_init(trie_t *t)
{
	puts("----->INIT");
	char *c = (char *) malloc(sizeof(char));
	*c = '\0';
	char *str = (char *) malloc(sizeof(char));
	*str = '\0';
	t->root = trieNode_new(c, str);
	puts("<-----INIT");
}

/* Given starting node in trie and one non-ending char,
find a level match between key initial and char */
trieNode_t *trie_levelMatch(trieNode_t *t, const char *c)
{
	if (t == NULL) return NULL;
	else 
	{
		if (*t->key == *c) return t;
		else return trie_levelMatch(t->next, c);
	}	
} 

void trie_destroyHelper(trieNode_t *t)
{
	if (t == NULL) return;
	trie_destroyHelper(t->next);
	trie_destroyHelper(t->child);
/*	curN--;*/
/*	if (*t->key != '\0') printf("Destroy node(%s) left curN=%d\n", t->str, curN);*/
/*	else printf("Destroy # left curN=%d\n", curN);*/
	if (t->key != NULL) free(t->key); 
	if (t->str != NULL) free(t->str);
	free(t);
	t = NULL;
	return;
}

void trie_destroy(trie_t *t)
{
	puts("#########################################");
	puts("------>destroy");
	trie_destroyHelper(t->root);
	puts("<------destroy");
}

trieNode_t *trieNode_list(const char *str, const char *ori) /*create a list of nodes*/
{
	trieNode_t *t;
	trieNode_t *h;
	trieNode_t *node;
	char *tmp;
	char *tmpstr;
	int i = 0;
	int j;
	int prefSize = strlen(ori) - strlen(str);
	printf("prefZise=%d", prefSize);
	int s;
/*	if (str[i] == '\0')*/
	while (str[i] != '\0')
	{
		/* new key */
		puts("IN WHILE");
		tmp = malloc(sizeof(char));
		*tmp = str[i];
		printf("%c i=%d\n", str[i], i);
		
		/* new string */
		puts("start malloc");
		s = prefSize + i + 2;
		tmpstr = malloc(s*sizeof(char));
		puts("get tmpstr");
		for (j = 0; j < (prefSize + i + 1); j++) 
		{
			tmpstr[j] = ori[j];
			printf("Put %c into tmpstr at j=%d\n", tmpstr[j], j);
		}
		tmpstr[j] = '\0';
		printf("%s\n", tmpstr);
		
		node = trieNode_new(tmp, tmpstr);
		if (i == 0) 
		{
			h = t = node;
		}
		else
		{
			t->child = node;
			t = node;
		}
		i++;
	}
	if (*t->key != '\0') t->count++;
	tmp = malloc(sizeof(char));
	*tmp = '\0'; 
	tmpstr = NULL;
	node = trieNode_new(tmp, tmpstr);
	t->child = node;
	t = node;
	puts("#");
	return h;
}

/*t is not the root*/
void trie_addHelper(trieNode_t *t, const char *str, const char *ori)
{
	trieNode_t *matchNode = trie_levelMatch(t, str);
	/*if non-empty, compare first level with first in str*/
	/*if find a match, neight of the next level is \0, compare next level*/
	if (matchNode != NULL && str[1] != '\0' && *matchNode->child->key != '\0')
	{
		t = trie_levelMatch(t, str);
		puts("# match # continue #");
		trie_addHelper(t->child, str + 1, ori);
		return;		
	}
	/*if find a match, next str is not \0, next node is \0, add a list to this node*/
	else if (matchNode != NULL && str[1] != '\0' && *matchNode->child->key == '\0')
	{
		t = trie_levelMatch(t, str);
		puts("# match # long str #");
		puts("release # in the trie");
		trie_destroyHelper(t->child);
		puts("Link new node to trie end");
		t->child = trieNode_list(str + 1, ori);
		return;
	}
	/*if find a match, next str is \0, next node is not \0, change count of this key*/
	/*if find a match, both next level are \0, change count of this key*/
	else if (matchNode != NULL && str[1] == '\0')
	{
		t = trie_levelMatch(t, str);
		puts("# match # str end #");
		t->count++;
		printf("Last char=%c count=%d\n", *str, t->count);
		return;
	}
	/*if find no match, add new node at the end of level, add new list to it*/
	else
	{
		printf("# no match str=%c, node=%c#\n", *str, *t->key);
		trieNode_t *end;
		end = t;
		while (end->next != NULL) end = end->next;
		puts("# no match: Add new list");
		end->next = trieNode_list(str, ori);
		printf("# node=%c -> next = str=%c#\n", *end->key, *str);
		puts("# no match: Add new list #END");
		return;
	}
}

void trie_add(trie_t *t, const char *str)
{
	/*if empty trie, add a list of str*/
	if (t->root->child == NULL) 
	{
		if (*t->root->key == '\0') puts("Empty trie with root node, add a list of str");
/*		char *tmp = malloc(sizeof(char));*/
/*		*tmp = '\0'; */
/*		char *tmpstr = malloc(sizeof(char));*/
/*		*tmpstr = '\0'; */
/*		t->root = trieNode_new(tmp, tmpstr);*/
		puts("Empty trie, add a list of str #END");
		t->root->child = trieNode_list(str, str);
		
	}
	/*if non-empty, compare first level with first in str*/
	else
	{
		puts("non empty: trie_add");
		trie_addHelper(t->root->child, str, str);
		puts("non empty: trie_add #END");
	}

}

int trie_sum(trieNode_t *t)
{
	if (t == NULL) return 0;
	else if (*t->key == '\0') return 0;
	else
	{
		return t->count + trie_sum(t->next) + trie_sum(t->child);
	}
}

/* start from root's child */
int trie_freq_countHelper(trieNode_t *t, const char *prefix)
{
	/*if no match, return 0*/
	/*if prefix is \0, return 0*/
	/*if t is \0, return 0*/
	if (t == NULL || prefix == NULL) 
	{
		puts("NULL root or prefix");
		return 0;
	}
	if (*t->key == '\0' || *prefix == '\0')
	{
		return 0; 
	}
	trieNode_t *matchNode = trie_levelMatch(t, prefix);
	if (matchNode == NULL) return 0;
	/*if find a match, neight of the next level is \0, go next level*/
	if (matchNode != NULL && *matchNode->child->key != '\0' && prefix[1] != '\0')
	{
		printf("%c matches %c\n", *matchNode->key, prefix[0]);
		return trie_freq_countHelper(matchNode->child, prefix + 1);
	}
	/*if find a match, next prefix is \0 next key not \0 , return count of this node*/
	if (matchNode != NULL && *matchNode->child->key != '\0' && prefix[1] == '\0')
	{
		/*sum all numbers*/
		puts("sum all numbers");
		return trie_sum(matchNode);
	}
	/*if find a match, next level are both \0 , return count of this node*/
	if (matchNode != NULL && *matchNode->child->key == '\0' && prefix[1] == '\0')
	{
		puts("two ends match\n");
		return matchNode->count;
	}
	/*if find a match, next prefix is not \0 next key \0 , return 0*/
	if (matchNode != NULL && *matchNode->child->key == '\0' && prefix[1] != '\0')
	{
		printf("Long prefix: node=%c and prefix=%c\n", *matchNode->key, prefix[0]);
		return 0;
	}
	return -1;
}


int trie_freq_count(trie_t *t, const char *prefix)
{
	/*if non-empty, compare first level with first in str*/
	if (t->root->child == NULL) 
	{
		puts("EMPTY!!!");	
		return 0;
	}
	else
	{
		puts("Begin count!!!");
		return trie_freq_countHelper(t->root->child, prefix);
	}
}

void trie_allStr(queue_t *q, trieNode_t *t)
{	
	if (t == NULL || *t->key == '\0') return;
	if (queue_size(q) == 0) trie_allStr(q, t->next);
	trie_allStr(q, t->child);
	if (t->count > 0)
	{
/*		printf("Enqueue %s\n", t->str);*/
		queue_enqueue(q, t->str);
	}
}

queue_t *trie_all_matchesHelper(trieNode_t *t, const char *prefix)
{
	puts("**************statr maching Helper******************************");
	queue_t *q = malloc(sizeof(queue_t));
	queue_init(q);
	if (t == NULL || prefix == NULL) return q;
	if (*t->key == '\0' || prefix == '\0') return q;
	
	trieNode_t *matchNode = trie_levelMatch(t, prefix);
	/* if match, neight next is \0, next iteration */
	if (matchNode != NULL && *matchNode->child->key != '\0' && prefix[1] != '\0')
	{
		printf("%s match %s, neight next is #, next iteration", matchNode->str, prefix);
		queue_destroy(q, 0);
		return trie_all_matchesHelper(matchNode->child, prefix + 1);
	}
	/* if match, both next is \0,  push this str into queue */
	if (matchNode != NULL && *matchNode->child->key == '\0' && prefix[1] == '\0')
	{
		printf("%s match %s, both next is #, enqueue", matchNode->str, prefix);
		queue_enqueue(q, matchNode->str);
		return q;
	}
	/* if match, next trie is \0, next prefix not, return null */
	if (matchNode != NULL && *matchNode->child->key == '\0' && prefix[1] != '\0')
	{
		printf("%s match %s, long prefix, null", matchNode->str, prefix);
		return q;
	}
	/* if match, next trie is not \0, next prefix \0, */
	if (matchNode != NULL && *matchNode->child->key != '\0' && prefix[1] == '\0')
	{
		puts("current queue is ");
		queue_print(q);
		printf("node key=%c, count=%d, str=%s\n", *matchNode->key, matchNode->count, matchNode->str);
		printf("pref[0]=%c, pref[1]=%c\n", prefix[0], prefix[1]);
		/*find all end points->str, if not null push into queue*/
		trie_allStr(q, matchNode);
		return q;
	}	
	/* if no match, NULL*/
	else return q;
}

queue_t *trie_all_matches(trie_t *t, const char *prefix)
{
	if (t->root == NULL || prefix == NULL) return NULL;
	puts("start _all_matches");
	return trie_all_matchesHelper(t->root->child, prefix);
}

void trie_longestSub(trieNode_t *t, trieNode_t* lnode, int flag)
{
	puts("--------------------------------------------");
	if (t == NULL) return;
	if (*t->key == '\0') return;
	printf("node=%s %d\nlnode=%s %d\n", 
	t->str, t->count, lnode->str, lnode->count);
	if (t->count > lnode->count){
		lnode->str = t->str;
		lnode->count = t->count;
		printf("Change lnode to %s\n", lnode->str);
	}
	if (flag && t->next != NULL) 
	{	
		printf("next--->%s %d\n", t->next->str, t->next->count);
		trie_longestSub(t->next, lnode, flag);
	}
	flag = 1;
	printf("child->%s %d\n", t->child->str, t->child->count);
	trie_longestSub(t->child, lnode, flag);
	return;
}

char *trie_most_freq_matchHelper(trieNode_t *t, const char *prefix)
{
	if (t == NULL || prefix == NULL) return NULL;
	if (*t->key == '\0' || prefix == '\0') return NULL;
	
	trieNode_t *matchNode = trie_levelMatch(t, prefix);
	/* if match, neight next is \0, next iteration */
	if (matchNode != NULL && *matchNode->child->key != '\0' && prefix[1] != '\0')
	{
		puts("Match. Neighter next empty");
		printf("node=%c, pref=%c\n", *matchNode->key, prefix[0]);
		return trie_most_freq_matchHelper(matchNode->child, prefix + 1);
	}
	/* if match, both next is \0, return current */
	if (matchNode != NULL && *matchNode->child->key == '\0' && prefix[1] == '\0')
	{
		puts("Both end");
		printf("node=%c, pref=%c\n", *matchNode->key, prefix[0]);
		return matchNode->str;
	}
	/* if match, next trie is \0, next prefix not, return null */
	if (matchNode != NULL && *matchNode->child->key == '\0' && prefix[1] != '\0')
	{
		puts("Too long prefix");
		printf("node=%c, pref=%c\n", *matchNode->key, prefix[0]);
		return NULL;
	}
	/* if match, next trie is not \0, next prefix \0, */
	if (matchNode != NULL && *matchNode->child->key != '\0' && prefix[1] == '\0')
	{
		/* return the big end node */
		puts("search longest in substr");
		printf("node=%c, pref=%c\n", *matchNode->key, prefix[0]);
		trieNode_t lnode;
		lnode.count = 0;
		lnode.str = "ORIGIN";
		trie_longestSub(matchNode, &lnode, 0);
		return lnode.str;
	}	
	/* if no match, NULL*/
	else return NULL;
}

char *trie_most_freq_match(trie_t *t, const char *prefix)
{
	if (t->root == NULL || prefix == NULL) return NULL;
	return trie_most_freq_matchHelper(t->root->child, prefix);
}

char *trie_longest_prefixHelper(trieNode_t *t, const char *str)
{
	if (t == NULL || str == NULL) return "";
	if (*t->key == '\0' || str == '\0') return "";
	trieNode_t *matchNode = trie_levelMatch(t, str);
	if (matchNode == NULL) return "";
	/* if match, both next not \0, and next also match, iterate*/
	if (matchNode != NULL && *matchNode->child->key != '\0' && str[1] != '\0')
	{
		if(trie_levelMatch(matchNode->child, str+1) != NULL)
		{
			puts("Match. Neighter next empty. Child match. ");
			printf("node=%c, pref=%c\n", *matchNode->key, str[0]);
			return trie_longest_prefixHelper(matchNode->child, str+1);
		}
		/* if match, both next not \0, and next not match, return node->str*/
		if (trie_levelMatch(matchNode->child, str+1) == NULL)
		{
			puts("Match. Neighter next empty. CHild no mathc. ");
			printf("node=%c, pref=%c\n nextN=%c, nextS=%c\n", 
			*matchNode->key, str[0],
			*matchNode->child->key, str[1]);
			return matchNode->str;
		}
	}
	/* if match, both next \0, return node->str */
	if (matchNode != NULL && *matchNode->child->key == '\0' && str[1] == '\0')
	{
		puts("Both End");
		printf("node=%c, pref=%c\n", *matchNode->key, str[0]);
		return matchNode->str;
	}
	/* if match, str next \0 return str*/
	if (matchNode != NULL && *matchNode->child->key != '\0' && str[1] == '\0')
	{
		puts("short prefix");
		printf("node=%c, pref=%c\n", *matchNode->key, str[0]);
		return matchNode->str;
	}
	/* if match, node next \0 return node->str*/
	if (matchNode != NULL && *matchNode->child->key == '\0' && str[1] != '\0')
	{
		puts("Too long prefix");
		printf("node=%c, pref=%c\n", *matchNode->key, str[0]);
		return matchNode->str;
	}
	return NULL;
}

char *trie_longest_prefix(trie_t *t, const char *str)
{

	puts("++++++++++++++++++++++++++++++++++++++");
	if (t->root == NULL ||str == NULL) return "";
	return trie_longest_prefixHelper(t->root->child, str);
}

void trie_printHelper(trieNode_t *itr)
{
	/*print current list*/
	if (itr == NULL) return;
	printf("%s", itr->str);
	printf("%d", itr->count);
	printf("->");

	if (*itr->key == '\0') 
	{
		putchar('\n');
		return;
	}
	if (*itr->child->key != '\0') {
/*		puts("Print child");*/
		trie_printHelper(itr->child);
	}
	if (itr->next != NULL) 
	{
/*		puts("Print next");*/
		putchar('\n');
		trie_printHelper(itr->next);
	}
}

void trie_print(trie_t *t)
{
	puts("Start print!");
	trie_printHelper(t->root->child);  
	puts("");
	puts("End print!");
}
