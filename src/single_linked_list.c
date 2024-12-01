#include "single_linked_list.h"
#include "stdlib.h"

SingleLinkedList *sll_create(int data_size){
    if( data_size<=0 || data_size > SLL_MAX_NODE_DATASIZE_BYTES )return NULL;
    SingleLinkedList *list = malloc(data_size);
    return list;
}