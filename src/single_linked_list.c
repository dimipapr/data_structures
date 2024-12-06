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

SLLNode *sllNodeCreate(SingleLinkedList* pList, void* pData){
    if( pList==NULL || pData==NULL)return NULL;
    SLLNode* node = malloc(sizeof(SLLNode));
    if(node==NULL){//malloc failure
        return NULL;
    }
    node->pData = malloc(pList->dataSize);
    if(node->pData==NULL){//malloc failure
        free(node);
        return NULL;
    }
    memcpy(node->pData, pData, pList->dataSize);
    node->pNext = NULL;
    return node;
}

SLLNode* sllInsertAtHead(SingleLinkedList *pList, void* pData){
    if(pList==NULL || pData==NULL)return NULL;
    SLLNode* node = sllNodeCreate(pList,pData);
    if(node == NULL)return NULL;
    node->pNext = pList->pHead;
    pList->pHead = node;
    return node;
}

int sllLength(SingleLinkedList *pList){
    if(pList == NULL)return SLL_NULL_LIST;
    SLLNode *node = pList->pHead;
    int count=0;
    while(node){
        count++;
        node=node->pNext;
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