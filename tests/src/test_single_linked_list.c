#include "minunit.h"
#include "single_linked_list.h"

#include <stdlib.h>
//sll_create
MU_TEST(test_sll_create__invalid_input){
	int data_size = 0;
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list==NULL, "sll_create() should return NULL with input data_size=0");
	data_size = -1;
	list = sll_create(data_size);
	mu_assert(list==NULL, "sll_create() should return NULL with input data_size<0");
	data_size = SLL_MAX_NODE_DATASIZE_BYTES+1;
	list = sll_create(data_size);
	mu_assert(list == NULL, "sll_create() should return NULL with input > SLL_MAX_NODE_DATASIZE_BYTES");
}

MU_TEST(test_sll_create__initial_values){
	int data_size=20;
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list != NULL, "sll_create() should not return NULL here");
	mu_assert(list->data_size == data_size, "list.data_size != data_size");
	mu_assert(list->head == NULL, "list.head should initialize to NULL");
	free(list);
}
//sll_node_create
MU_TEST(test_sll_node_create__bad_input){
	SingleLinkedList *null_list=NULL;
	int *null_data = NULL;
	SingleLinkedList *list = sll_create(sizeof(int));
	int data = 10;
	SLL_Node *node = sll_node_create(null_list, &data);
	mu_assert(node == NULL, "sll_node_create() should return NULL if list is NULL");
	node = sll_node_create(list, null_data);
	mu_assert(node == NULL, "sll_node_create() should return NULL if data is NULL");
	node = sll_node_create(null_list, null_data);
	mu_assert(node == NULL, "sll_node_create() should return NULL if both list and data is NULL");
	free(list);
}

MU_TEST(test_sll_node_create__initial_values){
	int data_size = sizeof(double);
	double data = 2e+10;
	SingleLinkedList *list = sll_create(data_size);
	SLL_Node *node = sll_node_create(list,&data);
	mu_assert(node != NULL, "node should not be NULL here");
	mu_assert(node->data != NULL, "node->data should not be NULL");
	mu_assert(node->next == NULL, "node->next should initialize to NULL");
	mu_assert(*(double*)node->data == data, "Bad node->data value");
	free(node->data);
	free(node);
	free(list);
}

//sll_node_destroy
MU_TEST(test_sll_node_destroy__bad_input){
	SLL_Node *node = NULL;
	sll_node_destroy(node);
	mu_check(1);
}
MU_TEST(test_sll_node_destroy__null_data){
	SingleLinkedList *list = sll_create(sizeof(int));
	mu_check(list);
	int data = 1;
	SLL_Node *node = sll_node_create(list, &data);
	mu_check(node);
	free(node->data);
	node->data = NULL;
	sll_node_destroy(node);
	free(list);
	mu_check(1);
}
MU_TEST(test_sll_node_destroy__normal_op){
	int data = 10;
	SingleLinkedList *list = sll_create(sizeof(int));
	mu_check(list);
	SLL_Node *node = sll_node_create(list, &data);
	mu_check(node);
	sll_node_destroy(node);
	mu_check(1);
	free(list);
}
//sll_destroy
MU_TEST(test_sll_destroy__bad_input){
	sll_destroy(NULL);
	mu_check(1);
}
MU_TEST(test_sll_destroy__empty_list){
	SingleLinkedList *list = sll_create(20);
	mu_check(list);
	sll_destroy(list);
	mu_check(1);
}
MU_TEST(test_sll_destroy__list_of_three_integers){
	SingleLinkedList *list = sll_create(sizeof(int));
	mu_check(list);
	int array_of_ints[]={0,1,2};
	list->head = sll_node_create(list, array_of_ints);
	mu_check(list->head);
	list->head->next = sll_node_create(list, array_of_ints+1);
	mu_check(list->head->next);
	list->head->next->next = sll_node_create(list, array_of_ints+2);
	mu_check(list->head->next->next);
	sll_destroy(list);
	mu_check(1);
}
//sll_get_tail
MU_TEST(test_sll_get_tail__bad_input){
	SingleLinkedList *list = NULL;
	SLL_Node *node = sll_get_tail(list);
	mu_assert(node == NULL, "sll_get_tail should return NULL with NULL list");
	int data_size = sizeof(int);
	list = sll_create(data_size);
	mu_check(list);
	node = sll_get_tail(list);
	mu_assert(node == NULL, "sll_get_tail should return NULL with empty list");
	sll_destroy(list);
}
MU_TEST(test_sll_get_tail__single_node_list){
	int data_size = sizeof(int);
	SingleLinkedList *list = sll_create(data_size);
	mu_check(list);
	int data = 10;
	list->head = sll_node_create(list, &data);
	SLL_Node *tail = sll_get_tail(list);
	mu_assert(tail!=NULL, "Should not be NULL");
	mu_assert(*(int*)tail->data = data, "IDK");
	sll_destroy(list);
}
MU_TEST(test_sll_get_tail__three_node_list){
	int data_size = sizeof(int);
	SingleLinkedList *list = sll_create(data_size);
	mu_check(list);
	int data0 = 10;
	int data1 = 20;
	int data2 = 30;
	list->head = sll_node_create(list, &data0);
	mu_check(list->head);
	list->head->next = sll_node_create(list, &data1);
	mu_check(list->head->next);
	list->head->next->next = sll_node_create(list, &data2);
	mu_check(list->head->next->next);
	SLL_Node *tail = sll_get_tail(list);
	mu_assert(tail!=NULL, "Should not be NULL");
	mu_assert(*(int*)tail->data = data2, "IDK");
	sll_destroy(list);
}
//sll_find_by_index
MU_TEST(test_sll_find_by_index__bad_input){
	int data_size = sizeof(int);
	SingleLinkedList *list = sll_create(data_size);
	mu_check(list);
	SLL_Node *node = sll_find_by_index(NULL,0);
	mu_assert(node==NULL, "Should return NULL with NULL list");
	node=sll_find_by_index(list,0);
	mu_assert(node == NULL, "sll_find_by_index should return NULL with empty list");
	int data = 10;
	list->head = sll_node_create(list,&data);
	mu_check(list->head);
	node = sll_find_by_index(list,-10);
	mu_assert(node == NULL, "Should return NULL with index not in [-1,inf]");
	sll_destroy(list);
}
MU_TEST(test_sll_find_by_index__find_head_exists){
	int data_size = sizeof(int);
	SingleLinkedList *list = sll_create(data_size);
	mu_check(list);
	int data=10;
	list->head = sll_node_create(list,&data);
	mu_check(list->head);
	SLL_Node *head = sll_find_by_index(list, 0);
	mu_assert(head != NULL, "sll_find_by_index should not return NULL here");
	mu_assert_int_eq(data, *(int*)head->data);
	sll_destroy(list);
}

//sll_append
// MU_TEST(test_sll_append__bad_input){
// 	int data_size = sizeof(int);
// 	SingleLinkedList *list = sll_create(data_size);
// 	SingleLinkedList *null_list = NULL;
// 	int data = 10;
// 	int *null_data = NULL;
// 	mu_check(list);
// 	SLL_Node *inserted_node = sll_append(null_list,&data,0);
// 	mu_assert(inserted_node == NULL, "sll_append() should return NULL with NULL list input");
// 	inserted_node = sll_append(list,null_data,0);
// 	mu_assert(inserted_node == NULL, "sll_append() should return NULL with NULL data input");
// 	inserted_node = sll_append(null_list, null_data,0);
// 	mu_assert(inserted_node == NULL, "sll_append() should return NULL with NULL list and data input");
// 	sll_destroy(list);
// }
// MU_TEST(test_sll_append__empty_list_insert_at_head){
// 	int data_size = sizeof(int);
// 	SingleLinkedList *list = sll_create(data_size);
// 	mu_check(list);
// 	int data = 10;
// 	SLL_Node *inserted_node = sll_append(list, &data, 0);
// 	mu_check(inserted_node);
// 	mu_assert(list->head == inserted_node, "Bad insertion");
// 	mu_assert(list->head->data == &data, "Bad data pointer after insertion");
// 	mu_assert(*(int*)list->head->data == data, "Bad data value after insertion");
// 	mu_assert(list->head->next==NULL, "Bad node->next after insertion");
// 	sll_destroy(list);
// }

MU_TEST_SUITE(test_sll_create){
	MU_RUN_TEST(test_sll_create__invalid_input);
	MU_RUN_TEST(test_sll_create__initial_values);
}
MU_TEST_SUITE(test_sll_node_create){
	MU_RUN_TEST(test_sll_node_create__bad_input);
	MU_RUN_TEST(test_sll_node_create__initial_values);
}
MU_TEST_SUITE(test_sll_node_destroy){
	MU_RUN_TEST(test_sll_node_destroy__bad_input);
	MU_RUN_TEST(test_sll_node_destroy__null_data);
	MU_RUN_TEST(test_sll_node_destroy__normal_op);
}
MU_TEST_SUITE(test_sll_destroy){
	MU_RUN_TEST(test_sll_destroy__bad_input);
	MU_RUN_TEST(test_sll_destroy__empty_list);
	MU_RUN_TEST(test_sll_destroy__list_of_three_integers);
}
MU_TEST_SUITE(test_sll_get_tail){
	MU_RUN_TEST(test_sll_get_tail__bad_input);
	MU_RUN_TEST(test_sll_get_tail__single_node_list);
	MU_RUN_TEST(test_sll_get_tail__three_node_list);
}
MU_TEST_SUITE(test_sll_find_by_index){
	MU_RUN_TEST(test_sll_find_by_index__bad_input);
	MU_RUN_TEST(test_sll_find_by_index__find_head_exists);
}
// MU_TEST_SUITE(test_sll_append) {
	// MU_RUN_TEST(test_sll_append__bad_input);
	// MU_RUN_TEST(test_sll_append__empty_list_insert_at_head);
// }

int main() {
	MU_RUN_SUITE(test_sll_create);
	MU_RUN_SUITE(test_sll_node_create);
	MU_RUN_SUITE(test_sll_node_destroy);
	MU_RUN_SUITE(test_sll_destroy);
	MU_RUN_SUITE(test_sll_get_tail);
	MU_RUN_SUITE(test_sll_find_by_index);

	MU_REPORT();
	return MU_EXIT_CODE;
}

