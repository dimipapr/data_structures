#include "minunit.h"
#include "single_linked_list.h"

MU_TEST(test_single_linked_list__add){
    mu_assert(1+1==add(1,1),"Hello?");
}

MU_TEST_SUITE(test_suite) {
	//MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_single_linked_list__add);
}

int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}

