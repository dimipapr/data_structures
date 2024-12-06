#include "minunit.h"
#include "single_linked_list.h"
#include <stdlib.h>

//sllCreate
MU_TEST(test_sllCreate_badInput){
	SingleLinkedList *list = sllCreate(0);
	mu_assert(list==NULL,"sllCreate should return NULL with data_size=0");
	list = sllCreate(-1);
	mu_assert(list==NULL,"sllCreate should return NULL with data_size=0");
	list = sllCreate(SLL_NODE_DATA_BYTES_MAX+1);
	mu_assert(list==NULL,"sllCreate should return NULL with data_size>SLL_NODE_DATA_BYTES_MAX");
}
MU_TEST(test_sllCreate_initialValues){
	int dataSize = sizeof(int);
	SingleLinkedList *list = sllCreate(dataSize);
	mu_assert(list, "Unexpected NULL from sllCreate");
	mu_assert(list->pHead == NULL, "list->pHead should initialize to NULL");
	mu_assert(list->dataSize == dataSize, "list->dataSize bad initialization");
}
MU_TEST_SUITE(suite_sllCreate){
	MU_RUN_TEST(test_sllCreate_badInput);
	MU_RUN_TEST(test_sllCreate_initialValues);
}

int main(){
	MU_RUN_SUITE(suite_sllCreate);
	MU_REPORT();
}