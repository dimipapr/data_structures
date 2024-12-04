#include "single_linked_list.h"
#include <stdlib.h>
#include <string.h>

SingleLinkedList *sll_create(int data_size){
    if (data_size <= 0 || data_size > SLL_NODE_DATA_BYTES_MAX)return NULL;
    SingleLinkedList *list = malloc(sizeof(SingleLinkedList));
    if(list){
        list->head = NULL;
        list->data_size = data_size;
        return list;
    }else{//malloc fails
        return NULL;
    }
}

SLL_Node *sll_node_create(SingleLinkedList *list, void *data){
    if( list==NULL || data==NULL )return NULL;
    SLL_Node *node = malloc(sizeof(SLL_Node));
    if(node == NULL)return NULL;
    node->data = malloc(list->data_size);
    if(node->data == NULL)goto err_data;
    memcpy(node->data,data,list->data_size);
    node->next = NULL;
    return node;
//malloc failure handling
err_data:free(node);
err_node:return NULL;
}