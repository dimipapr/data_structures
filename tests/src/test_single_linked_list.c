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
MU_TEST(test_sll_length){
    SingleLinkedList *list=NULL;
    mu_assert(sll_length(list)==-1,"Should return -1 when list arg is NULL");
    int data_size = sizeof(int);
    list = sll_init(data_size);
    mu_assert(sll_length(list)==0,"Should return 0 on empty list");
    int data = 87;
    sll_insert_at_head(list,&data);
    mu_assert(sll_length(list)==1,"Bad list length");
    free(list->head->data);
    free(list->head);
    free(list);
}

MU_TEST(test_sll_node_destroy){
    SingleLinkedListNode *node = NULL;
    sll_node_destroy(node);//should just run
    int data_size = sizeof(int);
    node = sll_node_init(data_size);
    sll_node_destroy(node);

}

MU_TEST(test_sll_traverse_print_int){
    //create a list with 3 nodes
    int a=0,b=1,c=2;
    int data_size = sizeof(int);
    SingleLinkedList *list=NULL;
    list = sll_init(data_size);
    sll_insert_at_head(list,&c);
    sll_insert_at_head(list,&b);
    sll_insert_at_head(list,&a);
    //sll_traverse(list,sll_print_int);
    sll_traverse(list,sll_node_destroy);
    free(list);
}
MU_TEST(test_sll_insert_at_tail){
    int a=0,b=1,c=2;
    int data_size = sizeof(int);
    SingleLinkedList *list = sll_init(data_size);
    sll_insert_at_tail(list,&a);
    sll_insert_at_tail(list,&b);
    sll_insert_at_tail(list,&c);
    sll_traverse(list,sll_print_int);
    sll_destroy(list);
}
MU_TEST(test_sll_get_node){
    SingleLinkedListNode *ret=sll_get_node(NULL,0);
    int data[] = {0,1,2};
    int data_size = sizeof(int);
    SingleLinkedList *list = sll_init(data_size);
    mu_assert(ret==NULL,"Should be NULL when list is null");
    sll_insert_at_head(list,data);
    sll_insert_at_tail(list,data+1);
    sll_insert_at_tail(list,data+2);
    ret = sll_get_node(list,-1);
    mu_assert(ret==NULL,"Should be null when index<0");
    ret = sll_get_node(list,3);
    mu_assert(ret==NULL,"Should be null when index is bigger than list length");
    int ret_data = *(int*)sll_get_node(list,0)->data;
    mu_assert(ret_data == 0,"Bad data from get_node()");
    ret_data = *(int*)sll_get_node(list,1)->data;
    mu_assert(ret_data == 1,"Bad data from get_node()");
    ret_data = *(int*)sll_get_node(list,2)->data;
    mu_assert(ret_data == 2,"Bad data from get_node()");
    sll_destroy(list);
}

MU_TEST(test_sll_find){
    int data[] = {8,76,-100};
    int data_size = sizeof(int);
    SingleLinkedList *list = sll_init(data_size);
    sll_insert_at_tail(list,data);
    sll_insert_at_tail(list,data+1);
    sll_insert_at_tail(list,data+2);
    //printf("%d",sll_find(list,data));
    mu_assert(sll_find(list,data)==0,"Wrong index returned");
    mu_assert(sll_find(list,data+1)==1,"Wrong index returned");
    mu_assert(sll_find(list,data+2)==2,"Wrong index returned");
    sll_destroy(list);

}

MU_TEST_SUITE(suite_sll){
    MU_SUITE_CONFIGURE(suite_sll_setup,suite_sll_teardown);
    MU_RUN_TEST(test_sll_init_bad_input);
    MU_RUN_TEST(test_sll_init_initial_values);
    MU_RUN_TEST(test_sll_node_init_bad_input);
    MU_RUN_TEST(test_sll_node_init_initial_values);
    MU_RUN_TEST(test_sll_insert_at_head_bad_input);
    MU_RUN_TEST(test_sll_insert_at_head_one_insert);
    MU_RUN_TEST(test_sll_length);
    MU_RUN_TEST(test_sll_node_destroy);
    MU_RUN_TEST(test_sll_traverse_print_int);
    MU_RUN_TEST(test_sll_insert_at_tail);
    MU_RUN_TEST(test_sll_get_node);
    MU_RUN_TEST(test_sll_find);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(suite_sll);
	MU_REPORT();
	return MU_EXIT_CODE;
}