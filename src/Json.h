
#ifndef JSON_HEADER
#define JSON_HEADER

#include "LinkedList.h"




/**
 * A JavaScript Object Notation
 */
typedef struct Json Json;




/**
 * Json methods table
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
    Json * (* new)(char const * const jsonString);

    /**
     * Destructor, sets the pointer to NULL
     * 
     * @param this - pointer to the instance to delete
     */
    void (* delete)(Json ** this);

    /**
     * Returns the json as a string
     * 
     * @param this - the instance to turn into a string
     * 
     * @return - string representation of the json
     */
    char const * (* toString)(Json const * const this);

    /**
     * Returns the list of parsed tokens
     * 
     * @param this - the json to get tokens of
     * 
     * @return - the parsed tokens
     */
    LinkedList * (* getTokens)(Json const * const this);

} _JsonMethods;




/**
 * Json class methods table
 */
extern _JsonMethods const * const _Json;




#endif /*JSON_HEADER */
