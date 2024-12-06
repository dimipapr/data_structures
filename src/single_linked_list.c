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
SLLNode* sllInsertAfter(SingleLinkedList* pList, SLLNode* pNode, SLLNode* pNewNode){
    if(pList==NULL || pNode == NULL || pNewNode==NULL)return NULL;
    pNewNode->pNext = pNode->pNext;
    pNode->pNext = pNewNode;
    return pNewNode;
}

SLLNode *sllInsertAt(SingleLinkedList* pList, SLLNode* pNewNode, int index){
    if( pList==NULL || pNewNode==NULL || index<-1 || index>SLL_NODES_MAX )return NULL;
    switch(index){
        case SLL_INDEX_HEAD:
            pNewNode->pNext=pList->pHead;
            pList->pHead=pNewNode;
            return pNewNode;
            break;
        case SLL_INDEX_TAIL:
            if(pList->pHead==NULL){
                pNewNode->pNext=pList->pHead;
                pList->pHead=pNewNode;
            }else{
                SLLNode* pTail=pList->pHead;
                while(pTail->pNext)pTail=pTail->pNext;
                pTail->pNext = pNewNode;
            }
            return pNewNode;
            break;
        default://insert at index (>0)
            if(pList->pHead==NULL){
                return NULL;
            }
            int count=0;
            SLLNode* pNode = pList->pHead;
            while(pNode->pNext && count < index-1){
                pNode = pNode->pNext;
                count++;
            }
            if(count == index-1){
                return sllInsertAfter(pList,pNode,pNewNode);
            }
            return NULL;
    }
}