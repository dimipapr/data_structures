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
//sll_insert
MU_TEST(test_sll_insert__bad_input){
	int data_size = 5*sizeof(int);
	int data[5] = {1,2,3,4,5};
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list, "Unexpected malloc failure");
	SLL_Node *node;
	node = sll_insert(NULL,data,0);
	mu_assert(node == NULL, "sll_insert should return NULL on NULL list input");
	node = sll_insert(list,NULL,0);
	mu_assert(node == NULL, "sll_insert should return NULL on NULL data input");
	node = sll_insert(NULL,NULL,0);
	mu_assert(node == NULL, "sll_insert should return NULL on NULL list and data input");
	node = sll_insert(list,data,-2);
	mu_assert(node == NULL, "sll_insert should return NULL with index<-1");
	node = sll_insert(list,data,SLL_NODES_MAX+1);
	mu_assert(node == NULL, "sll_insert should return NULL with index>SLL_NODES_MAX");
	free(list);
}
MU_TEST(test_sll_insert__head_on_empty_list){
	int data_size = 3*sizeof(int);
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list,"Unexpected malloc failure");
	int data1[3]={0,0,1};
	SLL_Node *node = sll_insert(list,data1,0);
	mu_assert(node,"Unexpected NULL return from sll_insert");
	mu_assert(node == list->head, "Bad pointer on list->head after insertion");
	mu_assert( memcmp(node->data,data1,list->data_size) == 0, "Bad node data after insertion");
	mu_assert(node->next == NULL, "node->next should be NULL");
	free(node->data);
	free(node);
	free(list);
}
MU_TEST(test_sll_insert__tail_on_empty_list){
	int data_size = 3*sizeof(int);
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list,"Unexpected malloc failure");
	int data1[3]={0,0,1};
	SLL_Node *node = sll_insert(list,data1,-1);
	mu_assert(node,"Unexpected NULL return from sll_insert");
	mu_assert(node == list->head, "Bad pointer on list->head after insertion");
	mu_assert(memcmp(node->data,data1,list->data_size)==0, "Bad node data after insertion");
	mu_assert(node->next == NULL, "node->next should be NULL");
	free(node->data);
	free(node);
	free(list);
}
MU_TEST(test_sll_insert__head_three_on_empty){
	int data_size = 3*sizeof(int);
	SingleLinkedList *list = sll_create(data_size);
	mu_assert(list,"Unexpected malloc failure");
	int data1[3]={0,0,1};
	int data2[3]={0,1,0};
	int data3[3]={1,0,0};
	SLL_Node *node = sll_insert(list,data1,0);
	mu_assert(node,"Unexpected NULL return from sll_insert");
	mu_assert(node == list->head, "Bad pointer on list->head after insertion");
	mu_assert(memcmp(node->data, data1, list->data_size) == 0,"Bad data");
	node = sll_insert(list,data2,0);
	mu_assert(node,"Unexpected NULL return from sll_insert");
	mu_assert(list->head == node, "Bad insertion");
	mu_assert(memcmp(node->data, data2, list->data_size) == 0,"Bad data");
	node = sll_insert(list,data3,0);
	mu_assert(node,"Unexpected NULL return from sll_insert");
	mu_assert(list->head == node, "Bad insertion");
	mu_assert(memcmp(node->data, data3, list->data_size) == 0,"Bad data");
	free(list->head->next->next->data);
	free(list->head->next->next);
	free(list->head->next->data);
	free(list->head->next);
	free(list->head->data);
	free(list->head);
	free(list);
}
//TODO add some more insertion tests

MU_TEST_SUITE(suite_sll_insert){
	MU_RUN_TEST(test_sll_insert__bad_input);
	MU_RUN_TEST(test_sll_insert__head_on_empty_list);
	MU_RUN_TEST(test_sll_insert__tail_on_empty_list);
	MU_RUN_TEST(test_sll_insert__head_three_on_empty);
}

int main(){
	MU_RUN_SUITE(suite_sll_create);
	MU_RUN_SUITE(suite_sll_node_create);
	MU_RUN_SUITE(suite_sll_traverse);
	MU_RUN_SUITE(suite_sll_insert);
	MU_REPORT();
}