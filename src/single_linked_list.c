#include "single_linked_list.h"
#include <stdlib.h>

SingleLinkedList *sll_create(int data_size){
    if (data_size <= 0 || data_size > SLL_NODE_DATA_BYTES_MAX)return NULL;
    SingleLinkedList *list = malloc(sizeof(SingleLinkedList));
    if(list){
        list->head = NULL;
        list->data_size = data_size;
        return list;
    }
    return NULL;
}