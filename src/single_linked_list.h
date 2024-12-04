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

/**
 * Creates a new Single Linked List and returns a pointer to it.
 * Returns NULL if it fails
 * @param data_size Size in bytes of node data
 * @returns A pointer to the new list. NULL if it fails.
 */
SingleLinkedList *sll_create(int data_size);

/**
 * Creates a new Single Linked List Node and returns a pointer to it.
 * Returns NULL on failure.
 * @param list The list the new node belongs to
 * @param data Pointer to the data to be copied in the node
 * @returns A pointer to the new node. NULL on failure
 */
SLL_Node *sll_node_create(SingleLinkedList *list, void *data);

/**
 * Go through the list and perform an action on each node
 * @param list
 * @param node_action A function pointer to a function manipulating each node
 */
void sll_traverse(SingleLinkedList *list,void (*node_action)(SLL_Node *node));

/**
 * Insert a new node in an existing single linked list at position designated by index.
 * @param list
 * @param data
 * @param index Index to insert new node. -1 for tail
 * @returns A pointer to the newly inserted node. NULL on failure
 */
SLL_Node* sll_insert(SingleLinkedList *list, void *data, int index);
#endif