#include "minunit.h"
#include "single_linked_list.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//sll_create
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
MU_TEST(test_sll_create__initial_values){
	int data_size = 10;
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list, "Should not return NULL here");
	mu_assert(list->data_size == data_size, "bad list->data_size after sll_create()");
	mu_assert(list->head == NULL, "list->head should be NULL after sll_create()");
	free(list);
}

MU_TEST_SUITE(suite_sll_create){
	// MU_SUITE_CONFIGURE(&setup_sll_create,&teardown_sll_create);
	MU_RUN_TEST(test_sll_create__bad_input);
	MU_RUN_TEST(test_sll_create__initial_values);
}

//sll_node_create
MU_TEST(test_sll_node_create__bad_input){
	int data_size = 10;
	SingleLinkedList *null_list = NULL;
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list != NULL, "Unexpected NULL return from sll_create");
	void *null_data = NULL;
	void *data = malloc(list->data_size);
	mu_assert(data, "Unexpected allocation failure");
	SLL_Node *node = sll_node_create(null_list,data );
	mu_assert(node == NULL, "sll_node_create should return NULL with NULL list input");
	node = sll_node_create(list, null_data);
	mu_assert(node == NULL, "sll_node_create should return NULL with NULL data input");
	node = sll_node_create(null_list, null_data);
	mu_assert(node == NULL, "sll_node_create should return NULL with NULL list and data input");
	free(list);
	free(data);
}
MU_TEST(test_sll_node_create__initial_values){
	int data_size = 10;
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list, "Unexpected malloc failure");
	char data[10] = "123456789";
	SLL_Node *node = sll_node_create(list,data);
	mu_assert(node, "Unexpected NULL return value from sll_node_create()");
	mu_assert(node->next == NULL, "node->next initial value should be NULL");
	mu_assert(memcmp(data,node->data,list->data_size) == 0, "node->data is not equal to given data after sll_node_create()");
	free(node->data);
	free(node);
	free(list);
}
MU_TEST_SUITE(suite_sll_node_create){
	MU_RUN_TEST(test_sll_node_create__bad_input);
	MU_RUN_TEST(test_sll_node_create__initial_values);
}
//sll_traverse
struct dog{
	char name[20];
	int age;
};
void grow_up_dog(SLL_Node *node){
	if(node == NULL || node->data == NULL)return;
	struct dog* this_dog = (struct dog*)(node->data);
	this_dog->age ++;
}
MU_TEST(test_sll_traverse__print_dogs){
	struct dog d1 = {.name="Skyloos",.age=5};
	struct dog d2 = {.name="Skylooooooos",.age=13};
	d1.name[0]='o';
	SingleLinkedList *list = sll_create(sizeof(struct dog));
	list->head = sll_node_create(list,&d1);
	list->head->next = sll_node_create(list,&d2);
	sll_traverse(list, &grow_up_dog);
	mu_assert( ((struct dog *)list->head->data)->age == d1.age+1, "Dog age did not bulge");
	mu_assert( ((struct dog *)list->head->next->data)->age == d2.age+1, "Dog age did not bulge");

	free(list->head->next->data);
	free(list->head->next);
	free(list->head->data);
	free(list->head);
	free(list);
	mu_check(1);
}
MU_TEST_SUITE(suite_sll_traverse){
	MU_RUN_TEST(test_sll_traverse__print_dogs);
}

int main(){
	MU_RUN_SUITE(suite_sll_create);
	MU_RUN_SUITE(suite_sll_node_create);
	MU_RUN_SUITE(suite_sll_traverse);
	MU_REPORT();
}