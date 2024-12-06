#include "single_linked_list.h"
#include <stdlib.h>
#include <string.h>

SingleLinkedList* sllCreate(int data_size){
    if ( data_size<=0 || data_size>SLL_NODE_DATA_BYTES_MAX )return NULL;
    SingleLinkedList *list = malloc(sizeof(SingleLinkedList));
    if(list){
        list->pHead = NULL;
        list->dataSize = data_size;
    }
    return list;
}