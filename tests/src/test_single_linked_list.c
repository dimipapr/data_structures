#include "minunit.h"
#include "single_linked_list.h"
#include <stdlib.h>

//sllCreate
MU_TEST(test_sllCreate_badInput){
	SingleLinkedList *pList = sllCreate(0);
	mu_assert(pList==NULL,"sllCreate should return NULL with data_size=0");
	pList = sllCreate(-1);
	mu_assert(pList==NULL,"sllCreate should return NULL with data_size=0");
	pList = sllCreate(SLL_NODE_DATA_BYTES_MAX+1);
	mu_assert(pList==NULL,"sllCreate should return NULL with data_size>SLL_NODE_DATA_BYTES_MAX");
}
MU_TEST(test_sllCreate_initialValues){
	int dataSize = sizeof(int);
	SingleLinkedList *pList = sllCreate(dataSize);
	mu_assert(pList, "Unexpected NULL from sllCreate");
	mu_assert(pList->pHead == NULL, "list->pHead should initialize to NULL");
	mu_assert(pList->dataSize == dataSize, "list->dataSize bad initialization");
	sllDestroy(pList);
}
MU_TEST_SUITE(suite_sllCreate){
	MU_RUN_TEST(test_sllCreate_badInput);
	MU_RUN_TEST(test_sllCreate_initialValues);
}
//sllNodeCreate
MU_TEST(test_sllNodeCreate_badInput){
	int dataSize = sizeof(int);
	SingleLinkedList *pList = sllCreate(dataSize);
	mu_check(pList);
	int data=10;
	SLLNode *pNode = sllNodeCreate(NULL,&data);
	mu_assert(pNode==NULL,"sllNodeCreate should return NULL with NULL pList input");
	pNode = sllNodeCreate(pList,NULL);
	mu_assert(pNode==NULL,"sllNodeCreate should return NULL with NULL pData input");
	pNode = sllNodeCreate(NULL,NULL);
	mu_assert(pNode==NULL,"sllNodeCreate should return NULL with NULL plist and pData input");
	sllDestroy(pList);
}
MU_TEST(test_sllNodeCreate_initialValues){
	int data_size = sizeof(int);
	SingleLinkedList *pList = sllCreate(data_size);
	mu_check(pList);
	int data=10;
	SLLNode *pNode = sllNodeCreate(pList, &data);
	mu_assert(pNode,"Unexpected NULL returned from sllNodeCreate");
	mu_assert(*(int*)(pNode->pData)==data, "Bad data copy after sllNodeCreate");
	mu_assert(pNode->pNext == NULL, "node->pNext initial value should be NULL");
	sllNodeDestroy(pNode);
	sllDestroy(pList);
}
MU_TEST_SUITE(suite_sllNodeCreate){
	MU_RUN_TEST(test_sllNodeCreate_badInput);
	MU_RUN_TEST(test_sllNodeCreate_initialValues);
}
//sllInsertAtHead
MU_TEST(test_sllInsertAtHead_badInput){
	int dataSize = sizeof(int);
	SingleLinkedList *pList = sllCreate(dataSize);
	mu_check(pList);
	int data=10;
	mu_assert(sllInsertAtHead(NULL,&data) == NULL, "sllInsertAtHead should return NULL with NULL list input");
	mu_assert(sllInsertAtHead(pList,NULL) == NULL, "sllInsertAtHead should return NULL with NULL data input");
	mu_assert(sllInsertAtHead(NULL,NULL) == NULL, "sllInsertAtHead should return NULL with NULL list and data input");
	sllDestroy(pList);
}
MU_TEST(test_sllInsertAtHead_insertFiftyNodes){
	SingleLinkedList *pList = sllCreate(sizeof(int));
	mu_check(pList);
	int data=10;
	for(int i=0;i<50;i++){
		sllInsertAtHead(pList,&data);		
	}
	mu_assert(sllLength(pList) == 50, "Bad list count");
	while(pList->pHead){
		SLLNode *tmp = pList->pHead;
		pList->pHead = pList->pHead->pNext;
		sllNodeDestroy(tmp);
	}
	mu_assert(sllLength(pList)==0, "List should be empty now");
	sllDestroy(pList);
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