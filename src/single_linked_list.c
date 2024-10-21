#include "single_linked_list.h"
#include <stdlib.h>

SingleLinkedList *sll_init(int data_size){
    if (data_size <= 0)return NULL;
    SingleLinkedList * list = malloc(sizeof(SingleLinkedList));
    list->data_size = data_size;
    list->head = NULL;
    return list;
}

SingleLinkedListNode *sll_node_init(int data_size){
    if (data_size<=0)return NULL;
    SingleLinkedListNode *node = malloc(sizeof(SingleLinkedListNode));
    node->data = NULL;
    node->next = NULL;
    return node;
}

SingleLinkedListNode *sll_insert_at_head(SingleLinkedList *list, void *data){
    if(list==NULL||data==NULL)return NULL;
}