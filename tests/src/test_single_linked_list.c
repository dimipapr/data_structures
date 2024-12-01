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
	SingleLinkedList *list=NULL;
	SLL_Node *node = sll_node_create(list);
	mu_assert(node == NULL, "sll_node_create() should return NULL if list is NULL");
}

MU_TEST(test_sll_node_create__initial_values){
	int data_size = 20;
	SingleLinkedList *list = sll_create(data_size);
	SLL_Node *node = sll_node_create(list);
	mu_assert(node != NULL, "node should not be NULL here");
	mu_assert(node->data != NULL, "node->data should not be NULL");
	mu_assert(node->next == NULL, "node->next should initialize to NULL");
	void *testptr = malloc(data_size);
	memcpy(testptr, node->data,data_size);//making sure node->data is accessible
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
	SingleLinkedList *list = sll_create(1);
	mu_check(list);
	SLL_Node *node = sll_node_create(list);
	mu_check(node);
	free(node->data);
	node->data = NULL;
	sll_node_destroy(node);
	free(list);
	mu_check(1);
}
MU_TEST(test_sll_node_destroy__normal_op){
	SingleLinkedList *list = sll_create(1);
	mu_check(list);
	SLL_Node *node = sll_node_create(list);
	mu_check(node);
	sll_node_destroy(node);
	mu_check(1);
}

MU_TEST_SUITE(test_suite) {
	//MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
	
	//sll_create
	MU_RUN_TEST(test_sll_create__invalid_input);
	MU_RUN_TEST(test_sll_create__initial_values);

	//sll_node_create
	MU_RUN_TEST(test_sll_node_create__bad_input);
	MU_RUN_TEST(test_sll_node_create__initial_values);
	//sll_node_destroy
	MU_RUN_TEST(test_sll_node_destroy__bad_input);
	MU_RUN_TEST(test_sll_node_destroy__null_data);
	MU_RUN_TEST(test_sll_node_destroy__normal_op);

}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

