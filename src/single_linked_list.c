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
    if(node == NULL)goto err_node;
    node->data = malloc(list->data_size);
    if(node->data == NULL)goto err_data;
    memcpy(node->data,data,list->data_size);
    node->next = NULL;
    return node;
//malloc failure handling
err_data:free(node);
err_node:return NULL;
}

void sll_traverse(SingleLinkedList *list, void (*node_action)(SLL_Node *node)){
    if( list==NULL || list->head==NULL )return;
    SLL_Node *node = list->head;
    while(node){
        SLL_Node *next = node->next;
        node_action(node);
        node = next;
    }
}
void sll_destroy(SingleLinkedList *list){
    if(list){
        if(list->head){
            SLL_Node *node = list->head;
            while(node){
                if(node->data)free(node->data);
                SLL_Node *next = node->next;
                free(node);
                node=next;
            }
        }
        free(list);
    }
}

SLL_Node* sll_insert(SingleLinkedList *list, void *data, int index){
    if( list==NULL || data==NULL || index<-1 || index>SLL_NODES_MAX)return NULL;
    SLL_Node *node = sll_node_create(list, data);
    if(index == -1){//insert at tail
        if(list->head == NULL){
            list->head = node;
            return node;
        }else{
            SLL_Node *tail = list->head;
            while(tail->next)tail=tail->next;
            tail->next=node;
            return node;
        }
    }else if(index == 0){//insert at head
        if(node == NULL)return NULL;//malloc fail
        node->next = list->head;
        list->head = node;
        return node;
    }else{
        free(node);
        return NULL;
    }
}