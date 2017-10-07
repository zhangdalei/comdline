#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zshell.h"

typedef struct list_head {
    char* command;
	char **parameters;
	int count;
    struct list_head *next, *prev;
}list_head;

#define LIST_HEAD_INIT(name) \
	struct list_head name = { .next = &(name), .prev = &(name) }

/** 初始化一个节点 */
static inline list_head* init_node (char* com, char** par, int cnt){
    list_head *node = (list_head*)malloc(sizeof(*node));
    node->command = com;
	node->parameters = par;
	node->count = cnt;
    node->next = node;
	node->prev = node;
	return node;
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/** 在链表头之后插入 */
static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}
// 遍历链表
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#endif
		
		