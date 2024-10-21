#include <stdlib.h>

#include "minunit.h"
#include "single_linked_list.h"


void suite_sll_setup(void){
   //
}
void suite_sll_teardown(void){
}
MU_TEST(test_sll_init_bad_input){
    SingleLinkedList *list;
    list = sll_init(0);
    mu_assert(list==NULL,"Not NULL when data_size = 0");
    list = sll_init(-1);
    mu_assert(list == NULL,"Not NULL when data_size = -1");
}
MU_TEST(test_sll_init_initial_values){
    int data_size = sizeof(int);
    SingleLinkedList *list = sll_init(data_size);
    mu_assert(list->data_size = data_size,"Bad data_size after init");
    mu_assert(list->head==NULL,"list->head is not NULL after init");
    free(list);
}
MU_TEST(test_sll_node_init_bad_input){
    int data_size;
    data_size = 0;
    SingleLinkedListNode *node = sll_node_init(data_size);
    mu_assert(node == NULL, "Should return NULL data_size=0"); 
    data_size = -1;
    node = sll_node_init(data_size);
    mu_assert(node == NULL, "Should return NULL data_size=-1"); 
}
MU_TEST(test_sll_node_init_initial_values){
    int data_size = sizeof(int);
    SingleLinkedListNode *node = sll_node_init(data_size);
    mu_assert(node->data!=NULL,"node->data is NULL after creation");
    mu_assert(node->next==NULL,"node->next is not null after creation");
    free(node->data);
    free(node);
}
MU_TEST(test_sll_insert_at_head_bad_input){
    int data_size = sizeof(int);
    int data = 25;
    int *datap=NULL;
    SingleLinkedList *list=NULL;
    SingleLinkedListNode *node;
    node = sll_insert_at_head(list,datap);
    mu_assert(node==NULL,"Not NULL with (NULL,NULL) input");
    datap = &data;
    node = sll_insert_at_head(list,datap);
    mu_assert(node==NULL,"Not NULL with (NULL,data) input");
    datap=NULL;
    list = sll_init(data_size);
    node = sll_insert_at_head(list,datap);
    mu_assert(node==NULL,"Not NULL with (list,NULL) input");
    free(list);
}
MU_TEST(test_sll_insert_at_head_one_insert){
    int data_size = sizeof(int);
    SingleLinkedList *list = sll_init(data_size);
    int data = 25;
    sll_insert_at_head(list, &data);
    mu_assert(list->head!=NULL,"list->head is null after insertion");
    mu_assert(list->head->next==NULL,"head->next should be NULL after insert in empty list");
    mu_assert(*(int*)(list->head->data)==data,"Data in list does not match data given");
    free(list->head->data);
    free(list->head);
    free(list);
}

MU_TEST_SUITE(suite_sll){
    MU_SUITE_CONFIGURE(suite_sll_setup,suite_sll_teardown);
    MU_RUN_TEST(test_sll_init_bad_input);
    MU_RUN_TEST(test_sll_init_initial_values);
    MU_RUN_TEST(test_sll_node_init_bad_input);
    MU_RUN_TEST(test_sll_node_init_initial_values);
    MU_RUN_TEST(test_sll_insert_at_head_bad_input);
    MU_RUN_TEST(test_sll_insert_at_head_one_insert);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(suite_sll);
	MU_REPORT();
	return MU_EXIT_CODE;
}