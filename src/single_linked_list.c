#include "single_linked_list.h"
#include <stdlib.h>
#include <string.h>

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
    if (node == NULL)return NULL;
    node->data = malloc(data_size);
    node->next = NULL;
    return node;
}

SingleLinkedListNode *sll_insert_at_head(SingleLinkedList *list, void *data){
    if(list==NULL||data==NULL)return NULL;
    SingleLinkedListNode *node = sll_node_init(list->data_size);
    if (node==NULL)return NULL;
    node->next = list->head;
    list->head = node;
    memcpy(list->head->data,data,list->data_size);
    return node;
}
int sll_length(SingleLinkedList *list){
}