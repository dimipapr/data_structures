#ifndef _SINGLE_LINKED_LIST_H
#define _SINGLE_LINKED_LIST_H

typedef struct _sll_node{
    struct _sll_node *next;
    void *data;
}SingleLinkedListNode;

typedef struct{
    SingleLinkedListNode *head;
    int data_size;
}SingleLinkedList;

SingleLinkedList *sll_init(int data_size);
SingleLinkedListNode *sll_node_init(int  data_size);

#endif