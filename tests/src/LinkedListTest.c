
#include <stddef.h>
#include <signal.h>
#include <criterion/criterion.h>

#include "../../src/LinkedList.h"




Test(LinkedList, instanciation_allocates_memory) {
    // given

    // when creating a new instance
    LinkedList * instance = _LinkedList->new(NULL);

    // then an usable memory block should be returned
    cr_assert_not_null(
        instance,
        "Creating a new instance should return a valid memory block"
    );
}


Test(LinkedList, destruction_free_memory) {
    // given an instance
    LinkedList * instance = _LinkedList->new(NULL);

    // when destroying it
    _LinkedList->delete(& instance);

    // then the memory block should have been freed and set to NULL
    cr_assert_null(
        instance,
        "Destroying the instance should free the memory and set the pointer to NULL"
    );
}


/**
 * FIXME: SIGDEV doesn't make test pass
 */
Test(LinkedList, destruction_frees_the_whole_list, .signal = SIGSEGV) {
    // given a list of several elements
    LinkedList * firstElement = _LinkedList->new("first");
    LinkedList * secondElement = _LinkedList->new("second");
    _LinkedList->append(& firstElement, secondElement);

    // when destroying from a given element
    _LinkedList->delete(& firstElement);
    
    // then next elements in the list should be destroyed too (segfault)
    _LinkedList->getContent(secondElement);
}


Test(LinkedList, stores_content) {
    // given some data
    char * data =  "test";

    // when creating a linked list element from it
    LinkedList * element = _LinkedList->new(data);

    // then the element should contain the data
    cr_assert_str_eq(
        (char *) _LinkedList->getContent(element),
        data,
        "The created element should contain the given content"
    );
}


Test(LinkedList, appends_element) {
    // given two elements
    LinkedList * firstElement = _LinkedList->new("first");
    LinkedList * secondElement = _LinkedList->new("second");

    // when appending the second element to the first one
    int status = _LinkedList->append(& firstElement, secondElement);

    // then the second element should be appended to the first one
    cr_assert_eq(
        status,
        0,
        "Appending an element should make it be the next in the list"
    );
}


Test(LinkedList, appending_element_on_null_list_sets_the_list) {
    // given a null list
    LinkedList * first = NULL;

    // when appending a valid element
    LinkedList * second = _LinkedList->new("second");
    _LinkedList->append(& first, second);

    // then the second element should become the first one
    cr_assert_eq(
        first,
        second,
        "Appending an element to null list should set the list to the element"
    );
}


Test(LinkedList, returns_next_element) {
    // given a list of two elements
    LinkedList * firstElement = _LinkedList->new("first");
    LinkedList * secondElement = _LinkedList->new("second");
    _LinkedList->append(& firstElement, secondElement);

    // when accessing the next element from the first one 
    LinkedList * nextElement = _LinkedList->nextElement(firstElement);

    // then the second element should be appended to the first one
    cr_assert_eq(
        nextElement,
        secondElement,
        "Accessing the next element should return the next element"
    );
}


Test(LinkedList, computes_the_size_list)
{
    // given a list of two elements
    LinkedList * firstElement = _LinkedList->new("first");
    LinkedList * secondElement = _LinkedList->new("second");
    _LinkedList->append(& firstElement, secondElement);

    // when computing the size of the list
    unsigned int size = _LinkedList->size(firstElement);
    
    // then it should be 2
    cr_assert_eq(
        size,
        2,
        "Size should be 2 for a list of two elements"
    );
}
