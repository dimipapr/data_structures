#include "minunit.h"
#include "single_linked_list.h"

MU_TEST(test_sll_create__bad_input){
	SingleLinkedList *list;
	int data_size = 0;
	list = sll_create(data_size);
	mu_assert(list==NULL,"sll_create should return NULL with data_size = 0");
	data_size = -1;
	list = sll_create(data_size);
	mu_assert(list==NULL,"sll_create should return NULL with data_size = <0");
	data_size = SLL_NODE_DATA_BYTES_MAX+1;
	mu_assert(list==NULL,"sll_create should return NULL with data_size > SLL_NODE_DATA_BYTES_MAX");
}

MU_TEST_SUITE(suite_sll_create){
	// MU_SUITE_CONFIGURE(&setup_sll_create,&teardown_sll_create);
	MU_RUN_TEST(test_sll_create__bad_input);
}

int main(){
	MU_RUN_SUITE(suite_sll_create);
	MU_REPORT();
}