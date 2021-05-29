
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Class.h"
#include "JsonToken.h"




/**
 * A json value
 */
typedef union
{
    JsonIntegerValue asInteger;
    JsonFloatValue asFloat;
    JsonBooleanValue asBoolean;
    JsonStringValue asString;
    JsonOperatorValue asOperator; 
} JsonValue;


struct JsonToken
{
    /**
     * The type of the token
     */
    JsonTokenType type;

    /**
     * The value stored in the token
     */
    JsonValue value;

    /**
     * The raw string that was used to create the token
     */
    char * rawString;
};




/**
 * Checks if the given token-string is a valid json operator
 * 
 * @param string - the token-string to check
 * 
 * @return - 1 if the token-string is a valid json operator, 0 otherwise
 */
static int __isOperatorToken(char const * const string);


/**
 * Checks if the given token-string is a valid json litteral boolean
 * 
 * @param string - the token-string to check
 * 
 * @return - 1 if the token-string is a valid json litteral boolean, 0 otherwise
 */
static int __isBooleanToken(char const * const string);


/**
 * Checks if the given token-string is a valid json litteral integer
 * 
 * @param string - the token-string to check
 * 
 * @return - 1 if the token-string is a valid json litteral integer, 0 otherwise
 */
static int __isIntegerToken(char const * const string);


/**
 * Checks if the given token-string is a valid json litteral float
 * 
 * @param string - the token-string to check
 * 
 * @return - 1 if the token-string is a valid json litteral float, 0 otherwise
 */
static int __isFloatToken(char const * const string);


/**
 * Checks if the given token-string is a valid json string
 * 
 * @param string - the token-string to check
 * 
 * @return - 1 if the token-string is a valid json string, 0 otherwise
 */
static int __isStringToken(char const * const string);


/**
 * Determines which type correspond to the string
 * If string is not a valid token, returns -1
 * 
 * @param string - the token-string to get type for
 * 
 * @return - corresponding JsonTokenType if valid, -1 otherwise
 */
static JsonTokenType __getTokenType(char const * const string);


/**
 * Returns the value stored in the string
 * Only handles valid token types
 * 
 * @param type - the type of token-string the string is, must be valid (no checks performed)
 * @param string - string to extract value from
 * 
 * @return - the value stored in the string
 */
static JsonValue __parseValue(JsonTokenType type, char * const string);




static JsonToken * new(char const * const string)
{
    JsonToken * this;

    if (string == NULL) {
        return NULL;
    }

    this = Class->new("JsonToken", sizeof(* this));

    if (this != NULL) {
        this->type = __getTokenType(string);
        if ((int) this->type == -1) {
            _JsonToken->delete(& this);
            return NULL;
        }

        this->rawString = malloc(strlen(string + 1));
        if (this->rawString == NULL) {
            _JsonToken->delete(& this);
            return NULL;    
        }
        strcpy(this->rawString, string);
        
        this->value = __parseValue(this->type, this->rawString);
    }

    return this;
}


static void delete(JsonToken ** this)
{
    if ((this == NULL) || (* this == NULL)) {
        return;
    }

    if ((* this)->rawString) {
        free((* this)->rawString);
        (* this)->rawString = NULL;
    }

    Class->delete((void **) this);
}


static JsonTokenType getType(JsonToken const * const this)
{
    return this->type;
}


static JsonIntegerValue asInteger(JsonToken const * const this)
{
    return this->value.asInteger;
}


static JsonFloatValue asFloat(JsonToken const * const this)
{
    return this->value.asFloat;
}


static JsonBooleanValue asBoolean(JsonToken const * const this)
{
    return this->value.asBoolean;
}


static JsonOperatorValue asOperator(JsonToken const * const this)
{
    return this->value.asOperator;
}


static JsonStringValue asString(JsonToken const * const this)
{
    return this->value.asString;
}


static char const * getRawString(JsonToken const * const this)
{
    return this->rawString;
}




static int __isOperatorToken(char const * const string)
{
    if (strlen(string) == 1) {
        switch (string[0]) {
            case JSON_OPERATOR_OBJECT_START:
            case JSON_OPERATOR_OBJECT_END:
            case JSON_OPERATOR_ARRAY_START:
            case JSON_OPERATOR_ARRAY_END:
            case JSON_OPERATOR_COLON:
            case JSON_OPERATOR_COMMA:
                return 1;
            default:
                return 0;
        }
    }

    return 0;
}


static int __isBooleanToken(char const * const string)
{
    return (strcmp(string, "false") == 0) || (strcmp(string, "true") == 0);
}


static int __isIntegerToken(char const * const string)
{
    unsigned int index;
    int signsFound = 0;

    for (index = 0; string[index] != '\0'; index++) {
        if (string[index] == '-') {
            signsFound++;
        } else if (string[index] < '0') {
            return 0;
        } else if (string[index] > '9') {
            return 0;
        }
    }

    if (signsFound) {
        return (signsFound == 1) && (string[0] == '-');
    }

    return 1;
}


static int __isFloatToken(char const * const string)
{
    unsigned int index;
    int signsFound = 0;
    int dotsFounds = 0;
    int dotPosition = 0;

    for (index = 0; string[index] != '\0'; index++) {
        if (string[index] == '-') {
            signsFound++;
        } else if (string[index] == '.') {
            dotsFounds++;
            dotPosition = index;
        } else if (string[index] < '0') {
            return 0;
        } else if (string[index] > '9') {
            return 0;
        }
    }

    if (dotsFounds != 1) {
        return 0;
    } else if (signsFound > 1) {
        return 0;
    } else if (signsFound) {
        return (string[0] == '-') && (dotPosition >= 2);
    }

    return dotPosition >= 1;
}


static int __isStringToken(char const * const string)
{
    unsigned int index;
    unsigned int stringLenght = strlen(string);

    if ((string[0] != '"') || (string[stringLenght - 1] != '"')) {
        return 0;
    }

    for (index = 1; index < stringLenght - 1; index++) {
        if ((string[index] == '"') && (string[index - 1] != '\\')) {
            return 0;
        }
    }

    return strlen(string) > 1;
}


static JsonTokenType __getTokenType(char const * const string)
{
    if (string == NULL) {
        return -1;
    }
    
    if (__isOperatorToken(string)) {
        return JSON_TOKEN_OPERATOR;
    }

    if (__isBooleanToken(string)) {
        return JSON_TOKEN_BOOLEAN;
    }

    if (__isIntegerToken(string)) {
        return JSON_TOKEN_INTEGER;
    }

    if (__isFloatToken(string)) {
        return JSON_TOKEN_FLOAT;
    }

    if (__isStringToken(string)) {
        return JSON_TOKEN_STRING;
    }

    return -1;
}


static JsonValue __parseValue(JsonTokenType type, char * const string)
{
    JsonValue parsedValue;

    switch (type) {
        case JSON_TOKEN_INTEGER:
            parsedValue.asInteger = atol(string);
            break;
        case JSON_TOKEN_FLOAT:
            parsedValue.asFloat = atof(string);
            break;
        case JSON_TOKEN_BOOLEAN:
            if (strcmp("false", string) == 0) {
                parsedValue.asBoolean = 0;
            } else {
                parsedValue.asBoolean = 1;
            }
            break;
        case JSON_TOKEN_OPERATOR:
            parsedValue.asOperator = string[0];
            break;
        case JSON_TOKEN_STRING:
            parsedValue.asString = string;
            break;
        /* we don't handle default case, type is supposed to be valid */
    }

    return parsedValue;
}




/**
 * Init JsonToken methods table
 */
static _JsonTokenMethods methods = {
    new,
    delete,
    getType,
    asInteger,
    asFloat,
    asBoolean,
    asOperator,
    asString,
    getRawString
};
_JsonTokenMethods const * const _JsonToken = & methods;
