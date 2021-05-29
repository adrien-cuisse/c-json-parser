#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Class.h"
#include "LinkedList.h"




struct LinkedList
{
    /**
     * The data stored in this element
     */
    void * content;

    /**
     * The next element in the list
     */
    LinkedList * nextElement;
};




static LinkedList * new(void * content)
{
    LinkedList * this;

    this = Class->new("LinkedList", sizeof(* this));

    if (this != NULL) {
        this->content = content;
    }

    return this;
}


static void delete(LinkedList ** this)
{
    if ((this == NULL) || (* this == NULL)) {
        return;
    }

    if ((* this)->nextElement != NULL) {
        _LinkedList->delete(& (* this)->nextElement);
    }

    Class->delete((void **) this);
}


static void * getContent(LinkedList const * const this)
{
    return this->content;
}


static int append(LinkedList ** this, LinkedList * const newElement)
{
    if ((this == NULL) || (newElement == NULL)) {
        return -1;
    }

    if (* this == NULL) {
        * this = newElement;
        return 0;
    } 

    return _LinkedList->append(& (* this)->nextElement, newElement);
}


static LinkedList * nextElement(LinkedList const * const this)
{
    return this->nextElement;
}


static unsigned int size(LinkedList const * const this)
{
    if (this == NULL) {
        return 0;
    }

    return 1 + _LinkedList->size(this->nextElement);
}




/**
 * Init LinkedList methods table
 */
static _LinkedListMethods methods = {
    new,
    delete,
    getContent,
    append,
    nextElement,
    size
};
_LinkedListMethods const * const _LinkedList = & methods;
