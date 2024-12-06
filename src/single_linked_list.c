#include "single_linked_list.h"
#include <stdlib.h>
#include <string.h>

SingleLinkedList* sllCreate(int data_size){
    if ( data_size<=0 || data_size>SLL_NODE_DATA_BYTES_MAX )return NULL;
    SingleLinkedList *pList = malloc(sizeof(SingleLinkedList));
    if(pList){
        pList->pHead = NULL;
        pList->dataSize = data_size;
    }
    return pList;
}

SLLNode *sllNodeCreate(SingleLinkedList* pList, void* pData){
    if( pList==NULL || pData==NULL)return NULL;
    SLLNode* pNode = malloc(sizeof(SLLNode));
    if(pNode==NULL){//malloc failure
        return NULL;
    }
    pNode->pData = malloc(pList->dataSize);
    if(pNode->pData==NULL){//malloc failure
        free(pNode);
        return NULL;
    }
    memcpy(pNode->pData, pData, pList->dataSize);
    pNode->pNext = NULL;
    return pNode;
}

SLLNode* sllInsertAtHead(SingleLinkedList *pList, void* pData){
    if(pList==NULL || pData==NULL)return NULL;
    SLLNode* pNode = sllNodeCreate(pList,pData);
    if(pNode == NULL)return NULL;
    pNode->pNext = pList->pHead;
    pList->pHead = pNode;
    return pNode;
}

int sllLength(SingleLinkedList *pList){
    if(pList == NULL)return SLL_NULL_LIST;
    SLLNode *pNode = pList->pHead;
    int count=0;
    while(pNode){
        count++;
        pNode=pNode->pNext;
    }
    return count;
}

void sllNodeDestroy(SLLNode *pNode){
    if(pNode == NULL)return;
    if(pNode->pData)free(pNode->pData);
    free(pNode);
}

void sllTraverse(SingleLinkedList* pList, void(*sll_node_action)(SLLNode* pNode)){

    
    if(pList==NULL || pList->pHead == NULL)return;
    SLLNode* pNode=pList->pHead;
    while(pNode){
        SLLNode* pNext=pNode->pNext;
        sll_node_action(pNode);
        pNode = pNext;
    }
}

void sllDestroy(SingleLinkedList* pList){
    if(pList == NULL)return;
    sllTraverse(pList, &sllNodeDestroy);
    free(pList);
}