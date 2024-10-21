#include <stdlib.h>

#include "minunit.h"
#include "single_linked_list.h"


int *data;
void suite_sll_setup(void){
    data = malloc(3*sizeof(int));
    data[0]=1;
    data[1]=2;
    data[2]=3;
}
void suite_sll_teardown(void){
    free(data);
}
MU_TEST(test_add){
    mu_assert(add(data[0],data[1])==data[2],"Should not salut.");
}

MU_TEST_SUITE(suite_sll){
    MU_SUITE_CONFIGURE(suite_sll_setup,suite_sll_teardown);
    MU_RUN_TEST(test_add);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(suite_sll);
	MU_REPORT();
	return MU_EXIT_CODE;
}