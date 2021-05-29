
#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER




/**
 * A linked list
 */
typedef struct LinkedList LinkedList;




/**
 * LinkedList methods table
 */
typedef struct
{
    /**
     * Constructor
     * 
     * @param data - the data to store in the element, will be stored internally
     * 
     * @return - a LinkedList element/instance if allocation succeeds, NULL otherwise
     */
    LinkedList * (* new)(void * data);

    /**
     * Destructor, sets the pointer to NULL
     * 
     * @param this - pointer to the instance to delete
     */
    void (* delete)(LinkedList ** this);

    /**
     * Returns the content stored in the element
     * 
     * @param this - the instance to get content from
     * 
     * @return - the content stored in the element
     */
    void * (* getContent)(LinkedList const * const this);

    /**
     * Appends a new element at the end of the list
     * 
     * @param this - the list that will store the new element at the end
     * @param newElement - the element to end at the end of the receiving list
     * 
     * @return - 0 on success, -1 on failure
     */
    int (* append)(LinkedList ** this, LinkedList * const newElement);

    /**
     * Returns the next element in the list
     * 
     * @param this - the element to get the next from
     * 
     * @return - the next element in the list, or NULL if there's none
     */
    LinkedList * (* nextElement)(LinkedList const * const this);

    /**
     * Returns the size of the list, from the current element to the end
     * 
     * @param this - the element to get the distance to the end of the list from
     * 
     * @return - the size of the list, from the current element to the end
     */
    unsigned int (* size)(LinkedList const * const this);

} _LinkedListMethods;




/**
 * LinkedList class methods table
 */
extern _LinkedListMethods const * const _LinkedList;




#endif /* LINKED_LIST_HEADER */
