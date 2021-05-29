#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Class.h"
#include "JsonToken.h"
#include "LinkedList.h"
#include "Json.h"




struct Json
{
    /**
     * The raw string used to build the json object
     */
    char * rawString;

    /**
     * The raw string, without white-spaces between tokens
     */
    char * trimmedString;

    /**
     * The list of tokens
     */
    LinkedList * tokens; 
};




/**
 * Computes the lenght of the trimmed json-string (@see __trimString)
 * 
 * @param jsonString - the json-string to get the lenght for
 * 
 * @return - the lenght of the trimmed string
 */
static unsigned int __trimmedStringLength(char const * const jsonString);


/**
 * Copies the json-string, without any white-spaces between tokens
 * 
 * @param jsonString - the json-string to trim
 * 
 * @return - the trimmed json-string
 */
static char * __trimString(char const * const jsonString);


/**
 * Parses the tokens from the trimmed string
 * 
 * @param this - the json object with a valid trimmed string to extract tokens from
 * 
 * @return - the list of parsed tokens
 */
static LinkedList * __extractTokens(Json const * this);




static Json * new(char const * const jsonString)
{
    Json * this;

    this = Class->new("Json", sizeof(* this));

    if (this != NULL) {
        this->rawString = calloc(strlen(jsonString) + 1, 1);
        if (this->rawString == NULL) {
            _Json->delete(& this);
            return NULL;
        }
        strcpy(this->rawString, jsonString);

        this->trimmedString = __trimString(this->rawString);
        if (this->trimmedString == NULL) {
            _Json->delete(& this);
            return NULL;
        }

        this->tokens = __extractTokens(this);
    }

    return this;
}


static void delete(Json ** this)
{
    if ((this == NULL) || (* this == NULL)) {
        return;
    }

    if ((* this)->rawString != NULL) {
        free((* this)->rawString);
        (* this)->rawString = NULL;
    }

    if ((* this)->trimmedString != NULL) {
        free((* this)->trimmedString);
        (* this)->trimmedString = NULL;
    }

    if ((* this)->tokens != NULL) {
        _LinkedList->delete(& (* this)->tokens);
    }

    Class->delete((void **) this);
}


static char const * toString(Json const * const this)
{
    return this->rawString;
}


static LinkedList * getTokens(Json const * const this)
{
    return this->tokens;
}




static unsigned int __trimmedStringLength(char const * const string)
{
    unsigned int stringIndex;
    int inQuotes = 0;
    unsigned int length = 0;

    for (stringIndex = 0; string[stringIndex] != '\0'; stringIndex++) {
        if ((string[stringIndex] == ' ') || (string[stringIndex] == '\t') || (string[stringIndex] == '\n')) {
            if (! inQuotes) {
                continue;
            }
        }

        if (string[stringIndex] == '"') {
            if (stringIndex == 0) {
                inQuotes = ! inQuotes;
            } else if (string[stringIndex - 1] != '\\') {
                inQuotes = ! inQuotes;
            }
        }

        length++;
    }

    return length;
}


static char * __trimString(char const * const string)
{
    unsigned int stringIndex;
    int inQuotes = 0;
    unsigned int length;
    char * trimmedString;
    unsigned int trimmedIndex;
    
    length = __trimmedStringLength(string);
    trimmedString = calloc(length + 1, 1);
    if (trimmedString == NULL) {
        return NULL;
    }

    for (trimmedIndex = 0, stringIndex = 0; string[stringIndex] != '\0'; stringIndex++) {
        if ((string[stringIndex] == ' ') || (string[stringIndex] == '\t') || (string[stringIndex] == '\n')) {
            if (! inQuotes) {
                continue;
            }
        }

        if (string[stringIndex] == '"') {
            if (stringIndex == 0) {
                inQuotes = ! inQuotes;
            } else if (string[stringIndex - 1] != '\\') {
                inQuotes = ! inQuotes;
            }
        }

        trimmedString[trimmedIndex] = string[stringIndex];
        trimmedIndex++;
    }

    return trimmedString;
}


static LinkedList * __extractTokens(Json const * this)
{
    char * tokenStart = this->trimmedString;
    char * tokenEnd = tokenStart + 1;
    char * tokenBuffer;
    LinkedList * tokens = NULL;
    JsonToken * currentToken;

    while (* (tokenEnd - 1) != '\0') {
        tokenBuffer = calloc(tokenEnd - tokenStart + 1, 1);
        if (tokenBuffer == NULL) {
            return NULL;
        }
        strncpy(tokenBuffer, tokenStart, tokenEnd - tokenStart);
        tokenBuffer[tokenEnd - tokenStart] = '\0';


        currentToken = _JsonToken->new(tokenBuffer);
        if (currentToken != NULL) {
            _LinkedList->append(& tokens, _LinkedList->new(currentToken));
            tokenStart = tokenEnd;
        }

        tokenEnd++;

        free(tokenBuffer);
    }

    return tokens;
}




/**
 * Init LinkedList methods table
 */
static _JsonMethods methods = {
    new,
    delete,
    toString,
    getTokens
};
_JsonMethods const * const _Json = & methods;
