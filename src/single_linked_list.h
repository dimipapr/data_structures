/**
 * Definitions for a generic single linked list implementation
 */
#ifndef SINGLE_LINKED_LIST
#define SINGLE_LINKED_LIST

#define SLL_NODES_MAX 512
#define SLL_NODE_DATA_BYTES_MAX 512

/**
 * Struct representing a generic single linked list node
 */
typedef struct SLL_Node{
    struct SLL_Node *next;  /**Next node. NULL if empty */
    void *data;             /**Node data */
}SLL_Node;

/**
 * Struct representing a generic single linked list.
 */
typedef struct  SingleLinkedList
{
    int data_size; /**List node field data size. */
    SLL_Node *head; /**Pointer to the first node */
}SingleLinkedList;

#endif