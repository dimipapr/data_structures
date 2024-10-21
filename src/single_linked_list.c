#include "single_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
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

SingleLinkedListNode *sll_node_destroy(SingleLinkedListNode *node){
    if (node == NULL)return 0;
    free(node->data);
    free(node);
    return 0;
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
SingleLinkedListNode *sll_insert_at_tail(SingleLinkedList *list, void *data){
    if(list==NULL||data==NULL)return NULL;
    //create node
    SingleLinkedListNode *newNode = sll_node_init(list->data_size);
    memcpy(newNode->data,data,list->data_size);
    //find tail
    SingleLinkedListNode *node=list->head;
    if(node == NULL){list->head = newNode;}
    else{
        while(node->next != NULL)node = node->next;
        node->next = newNode;
    }
    return newNode;
}
int sll_length(SingleLinkedList *list){
    if (list==NULL)return -1;
    int count =0;
    SingleLinkedListNode *node = list->head;
    while(node != NULL){
        node = node->next;
        count ++;
    }
    return count;
}

void sll_traverse(
    SingleLinkedList *list,
    SingleLinkedListNode *(*what_to_do_with_node)(SingleLinkedListNode *node)
)
{
    if(list==NULL)return;
    SingleLinkedListNode *node = list->head;
    SingleLinkedListNode *next;
    while(node != NULL){
        next = node->next;
        what_to_do_with_node(node);
        node=next;
    } 
}

void sll_destroy(SingleLinkedList *list){
    sll_traverse(list, sll_node_destroy);
    free(list);
}


SingleLinkedListNode *sll_print_int(SingleLinkedListNode *node){
    if (node==NULL)return NULL;
    int data = *(int *)node->data;
    printf("%d",data);
    return NULL;
}

SingleLinkedListNode *sll_get_node(SingleLinkedList *list, int index){
    if(list == NULL||index<0)return NULL;
    if(sll_length(list)<index)return NULL;
    SingleLinkedListNode *node = list->head;
    int count=0;
    while(node!=NULL){
        if(count == index)return node;
        node = node->next;
        count++;
    }
    return NULL;
}

int sll_find(SingleLinkedList *list, void *data){
    if(list==NULL || data==NULL)return -3;//BAD INPUT
    if(list->head == NULL)return -2;//EMPTY LIST
    SingleLinkedListNode *node = list->head;
    int index = 0;
    while(node != NULL){
        if(0==memcmp(data,node->data,list->data_size))return index;
        node=node->next;
        index++; 
    }
    return -1; //NO MATCH
}
