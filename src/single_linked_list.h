#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#define SLL_MAX_NODE_DATASIZE_BYTES 256

/**
 * A struct representing a Single Linked List node
 */
typedef struct SLL_Node{
    struct SLL_Node *next; /** Pointer to the next node */
    void *data;             /**Pointer to the node data */
}SLL_Node;

/**
 * A struct representing a Single Linked List.
 */
typedef struct SingleLinkedList{
    int data_size; /** Size in bytes of the node data field */
    SLL_Node *head; /** Pointer to the head of the list */
}SingleLinkedList;

/**
 * Create a new single linked list.
 * @param[in] data_size Size in bytes of the node data field
 * @returns A pointer to the created single linked list, NULL if data_size<=0 or data_size>SLL_MAX_NODE_DATASIZE_BYTES
 */
SingleLinkedList *sll_create(int data_size);

/**
 * Create a new Single Linked List Node
 * @param[in] list Single linked list associated with the created node
 * @returns A pointer to the created single linked list node, NULL if list is NULL
 */
SLL_Node *sll_node_create(SingleLinkedList *list);

#endif