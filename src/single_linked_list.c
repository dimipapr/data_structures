#include "single_linked_list.h"
#include <stdlib.h>

SingleLinkedList *sll_init(int data_size){
    if (data_size <= 0)return NULL;
    SingleLinkedList * list = malloc(sizeof(SingleLinkedList));
    list->data_size = data_size;
    list->head = NULL;
    return list;
}