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
	free(list);
}
MU_TEST_SUITE(suite_sllCreate){
	MU_RUN_TEST(test_sllCreate_badInput);
	MU_RUN_TEST(test_sllCreate_initialValues);
}
//sllNodeCreate
MU_TEST(test_sllNodeCreate_badInput){
	int dataSize = sizeof(int);
	SingleLinkedList *list = sllCreate(dataSize);
	mu_check(list);
	int data=10;
	SLLNode *node = sllNodeCreate(NULL,&data);
	mu_assert(node==NULL,"sllNodeCreate should return NULL with NULL pList input");
	node = sllNodeCreate(list,NULL);
	mu_assert(node==NULL,"sllNodeCreate should return NULL with NULL pData input");
	node = sllNodeCreate(NULL,NULL);
	mu_assert(node==NULL,"sllNodeCreate should return NULL with NULL plist and pData input");
	free(list);
}
MU_TEST(test_sllNodeCreate_initialValues){
	int data_size = sizeof(int);
	SingleLinkedList *list = sllCreate(data_size);
	mu_check(list);
	int data=10;
	SLLNode *node = sllNodeCreate(list, &data);
	mu_assert(node,"Unexpected NULL returned from sllNodeCreate");
	mu_assert(*(int*)(node->pData)==data, "Bad data copy after sllNodeCreate");
	mu_assert(node->pNext == NULL, "node->pNext initial value should be NULL");
	free(node->pData);
	free(node);
	free(list);
}
MU_TEST_SUITE(suite_sllNodeCreate){
	MU_RUN_TEST(test_sllNodeCreate_badInput);
	MU_RUN_TEST(test_sllNodeCreate_initialValues);
}
//sllInsertAtHead
MU_TEST(test_sllInsertAtHead_badInput){
	int dataSize = sizeof(int);
	SingleLinkedList *list = sllCreate(dataSize);
	mu_check(list);
	int data=10;
	SLLNode *node = sllNodeCreate(list, &data);
	mu_check(node);
	mu_assert(sllInsertAtHead(NULL,node) == NULL, "sllInsertAtHead should return NULL with NULL list input");
	mu_assert(sllInsertAtHead(list,NULL) == NULL, "sllInsertAtHead should return NULL with NULL node input");
	mu_assert(sllInsertAtHead(NULL,NULL) == NULL, "sllInsertAtHead should return NULL with NULL list and node input");
	free(list);
	free(node->pData);
	free(node);
}
MU_TEST(test_sllInsertAtHead_insertFiftyNodes){
	SingleLinkedList *list = sllCreate(sizeof(int));
	mu_check(list);
	int data=10;
	for(int i=0;i<50;i++){
		SLLNode* node = sllNodeCreate(list, &data);
		mu_check(node);
		node->pNext = list->pHead;
		list->pHead = node;
	}
	mu_assert(sllLength(list) == 50, "Bad list count");
	while(list->pHead){
		SLLNode *tmp = list->pHead;
		list->pHead = list->pHead->pNext;
		free(tmp->pData);
		free(tmp);
	}
	mu_assert(sllLength(list)==0, "List should be empty now");
	free(list);

}
MU_TEST_SUITE(suite_sllInsertAtHead){
	MU_RUN_TEST(test_sllInsertAtHead_badInput);
	MU_RUN_TEST(test_sllInsertAtHead_insertFiftyNodes);
}
int main(){
	MU_RUN_SUITE(suite_sllCreate);
	MU_RUN_SUITE(suite_sllNodeCreate);
	MU_RUN_SUITE(suite_sllInsertAtHead);
	MU_REPORT();
}