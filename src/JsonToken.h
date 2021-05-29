
#ifndef JSON_TOKEN_HEADER
#define JSON_TOKEN_HEADER




/**
 * A json litteral integer
 */
typedef long JsonIntegerValue;


/**
 * A json litteral float
 */
typedef double JsonFloatValue;


/**
 * A json litteral boolean
 */
typedef char JsonBooleanValue;


/**
 * A json string
 */
typedef char * JsonStringValue;


/**
 * A json operator
 */
typedef char JsonOperatorValue;


/**
 * A json operator may be any of these
 */
typedef enum
{
    JSON_OPERATOR_OBJECT_START = '{',
    JSON_OPERATOR_OBJECT_END = '}',
    JSON_OPERATOR_ARRAY_START = '[',
    JSON_OPERATOR_ARRAY_END = ']',
    JSON_OPERATOR_COLON = ':',
    JSON_OPERATOR_COMMA = ','
} JsonOperator;


/**
 * Differents types the token may have
 */
typedef enum
{
    JSON_TOKEN_INTEGER,
    JSON_TOKEN_FLOAT,
    JSON_TOKEN_STRING,
    JSON_TOKEN_OPERATOR,
    JSON_TOKEN_BOOLEAN
} JsonTokenType;


/**
 * A json token
 */
typedef struct JsonToken JsonToken;




/**
 * JsonToken methods table
 */
typedef struct
{
    /**
     * Constructor
     * 
     * @param string - the string representation of the token
     * 
     * @return - a JsonToken instance if the token-string is valid and allocation succeeds, NULL otherwise
     */
    JsonToken * (* new)(char const * const string);

    /**
     * Destructor, sets the pointer to NULL
     * 
     * @param this - pointer to the instance to delete
     */
    void (* delete)(JsonToken ** this);

    /**
     * Returns the type of the token
     * 
     * @param this - the instance to get the type for
     * 
     * @return - the type of the token
     */
    JsonTokenType (* getType)(JsonToken const * const this);

    /**
     * Evaluates the token as an integer
     * 
     * @param this - the instance to evaluate as an integer
     * 
     * @return - the integer value stored in the token
     */
    JsonIntegerValue (* asInteger)(JsonToken const * const this);

    /**
     * Evaluates the token as a float
     * 
     * @param this - the instance to evaluate as a float
     * 
     * @return - the float value stored in the token
     */
    JsonFloatValue (* asFloat)(JsonToken const * const this);

    /**
     * Evaluates the token as a boolean
     * 
     * @param this - the instance to evaluate as a boolean
     * 
     * @return - the boolean value stored in the token
     */
    JsonBooleanValue (* asBoolean)(JsonToken const * const this);

    /**
     * Evaluates the token as an operator
     * 
     * @param this - the instance to evaluate as an operator
     * 
     * @return - the operator stored in the token
     */
    JsonOperatorValue (* asOperator)(JsonToken const * const this);

    /**
     * Evaluates the token as a string
     * 
     * @param this - the instance to evaluate as a string
     * 
     * @return - the string value stored in the token
     */
    JsonStringValue (* asString)(JsonToken const * const this);

    /**
     * Returns the raw string the token represents
     * 
     * @param this - the token to get raw string for
     * 
     * @return - the raw string the token represents
     */
    char const * (* getRawString)(JsonToken const * const this);

} _JsonTokenMethods;




/**
 * JsonToken class methods table
 */
extern _JsonTokenMethods const * const _JsonToken;  




#endif /* JSON_TOKEN_HEADER */
