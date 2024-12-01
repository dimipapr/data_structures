#include "minunit.h"
#include "single_linked_list.h"

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

MU_TEST(test_sll_create__normal_operation){
	int data_size=20;
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list != NULL, "sll_create() should not return NULL here");
}

MU_TEST_SUITE(test_suite) {
	//MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_sll_create__invalid_input);
	MU_RUN_TEST(test_sll_create__normal_operation);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

