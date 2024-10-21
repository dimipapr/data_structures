#include <stdlib.h>

#include "minunit.h"
#include "single_linked_list.h"


void suite_sll_setup(void){
   //
}
void suite_sll_teardown(void){
}
MU_TEST(sll_init_bad_input){
    SingleLinkedList *list;
    list = sll_init(0);
    mu_assert(list==NULL,"Not NULL when data_size = 0");
    list = sll_init(-1);
    mu_assert(list == NULL,"Not NULL when data_size = -1");
}
MU_TEST(sll_init_initial_values){
    int data_size = sizeof(int);
    SingleLinkedList *list = sll_init(data_size);
    mu_assert(list->data_size = data_size,"Bad data_size after init");
    mu_assert(list->head==NULL,"list->head is not NULL after init");

}

MU_TEST_SUITE(suite_sll){
    MU_SUITE_CONFIGURE(suite_sll_setup,suite_sll_teardown);
    MU_RUN_TEST(sll_init_bad_input);
    MU_RUN_TEST(sll_init_initial_values);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(suite_sll);
	MU_REPORT();
	return MU_EXIT_CODE;
}