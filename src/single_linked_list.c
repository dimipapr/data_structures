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

void sll_traverse(SingleLinkedList *list, void (*node_action)(SLL_Node *node)){
    if (list == NULL)return;
    SLL_Node *node = list->head;
    while(node != NULL){
        SLL_Node *next = node->next;
        node_action(node);
        node = next;
    }
}

void sll_destroy(SingleLinkedList *list){
    if (list == NULL) return;
    sll_traverse(list, &sll_node_destroy);
    free(list);
}

// SLL_Node *sll_append(SingleLinkedList *list, void *data, int index){
//     if(list == NULL || data == NULL)return NULL;

// }

SLL_Node *sll_get_tail(SingleLinkedList *list){
    if(list == NULL || list->head == NULL) return NULL;
    SLL_Node *node = list->head;
    while(node->next != NULL) node = node->next;
    return node;
}

SLL_Node *sll_find_by_index(SingleLinkedList *list, int index){
    if (list == NULL || index < -1)return NULL;
    if(index == -1){
        return sll_get_tail(list);
    }
    SLL_Node *node = list->head;
    int node_index = 0;
    while( node!=NULL && node_index < index ){
        node_index++;
        node = node->next;
    }
    return node;
}