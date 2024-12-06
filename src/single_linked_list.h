/**
 * Definitions for a generic single linked list implementation
 */
#ifndef SINGLE_LINKED_LIST
#define SINGLE_LINKED_LIST

#define SLL_NODES_MAX 512
#define SLL_NODE_DATA_BYTES_MAX 512

#define SLL_NULL_LIST -1

#define SLL_INDEX_HEAD 0
#define SLL_INDEX_TAIL -1

/**
 * Struct representing a generic single linked list node
 */
typedef struct SLLNode{
    struct SLLNode *pNext;  /**Next node. NULL if empty */
    void *pData;             /**Node data */
}SLLNode;

/**
 * Struct representing a generic single linked list.
 */
typedef struct  SingleLinkedList
{
    int dataSize; /**List node field data size. */
    SLLNode *pHead; /**Pointer to the first node */
}SingleLinkedList;

SLLNode*            sllNodeCreate(SingleLinkedList* pList, void* pData);
SingleLinkedList*   sllCreate(int data_size);
int                 sllLength(SingleLinkedList* pList);
void                sllTraverse(SingleLinkedList* pList, void(*sll_node_action)(SLLNode* pNode));
void                sllDestroy(SingleLinkedList* pList);
void                sllNodeDestroy(SLLNode* pNode);

SLLNode*            sllInsertAfter(SingleLinkedList* pList, SLLNode* pNode, SLLNode* pNewNode);
SLLNode*            sllInsertAt(SingleLinkedList* pList, SLLNode* pNode, int index);

#endif