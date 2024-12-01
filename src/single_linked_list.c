#include "single_linked_list.h"
#include <stdlib.h>
#include <string.h>

SingleLinkedList *sll_create(int data_size){
    if( data_size<=0 || data_size > SLL_MAX_NODE_DATASIZE_BYTES )return NULL;
    SingleLinkedList *list = malloc(sizeof(SingleLinkedList));
    if(list == NULL)return NULL;
    list->data_size = data_size;
    list->head = NULL;
    return list;
}

SLL_Node *sll_node_create(SingleLinkedList *list, void *data){
    if (list == NULL || data == NULL) return NULL;
    SLL_Node *node = malloc(sizeof(SLL_Node));
    if(node == NULL)return NULL;//malloc fails
    node->data = malloc(list->data_size);
    if (node->data == NULL){ //malloc fails
        free(node);
        return NULL;
    }
    memcpy(node->data, data, list->data_size);
    node->next = NULL;
    return node;
}

void sll_node_destroy(SLL_Node *node){
    if(node == NULL)return;
    if(node->data != NULL)free(node->data);
    free(node);
}