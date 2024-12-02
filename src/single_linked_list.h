#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#define SLL_MAX_NODE_DATASIZE_BYTES 256
#define SLL_MAX_LIST_SIZE 256

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
 * @param[in] data Data to be copied in the node
 * @returns A pointer to the created single linked list node, NULL if list is NULL
 */
SLL_Node *sll_node_create(SingleLinkedList *list, void *data);

/**
 * Frees all associated memory of a given single linked list node
 * @param[in] node
 * @returns Nothing
 */
void sll_node_destroy(SLL_Node *node);

/**
 * Traverses through the list and performs an action on every node
 * @param[in] list
 * @param[in] node_action Function pointer to the action to be performed on each node
 * @returns Nothing
 */
void sll_traverse(SingleLinkedList *list, void (*node_action)(SLL_Node *node));

/**
 * Frees all associated memory of a single linked list
 * @param[in] list
 * @returns Nothing
 */
void sll_destroy(SingleLinkedList *list);

/**
 * Finds node at given index.
 * @param list
 * @param index -1 for list tail
 * @returns Pointer to node. NULL if list is smaller than given index
 */
SLL_Node *sll_find_by_index(SingleLinkedList *list, int index);

/**
 * Get the list's last node. NULL if list is NULL or empty
 * @param[in] list
 * @returns List's tail
 */
SLL_Node *sll_get_tail(SingleLinkedList *list);

/**
 * Creates a new node with given data and appends it on the list at the designated index.
 * Use index=-1 for insertion at list tail
 * @param[in] list Single linked list to append node to
 * @param[in] data Pointer to node data
 * @param[in] index Position to append new node
 * @returns Pointer to inserted node if successfull
 */
// SLL_Node *sll_append(SingleLinkedList *list, void *data, int index);

#endif