
#include <criterion/criterion.h>

#include "../../src/Class.h"




Test(Class, instanciation_allocates_memory) {
    // given

    // when creating a new instance
    void * instance = Class->new("", 42);

    // then an usable memory block should be returned
    cr_assert_not_null(
        instance,
        "Creating a new instance should return a valid memory block"
    );
}


Test(Class, destruction_frees_memory) {
    // given an instance
    void * instance = Class->new("", 42);

    // when destroying it
    Class->delete(& instance);

    // then the memory block should have been freed and set to NULL
    cr_assert_null(
        instance,
        "Destroying the instance should free the memory and set the pointer to NULL"
    );
}
