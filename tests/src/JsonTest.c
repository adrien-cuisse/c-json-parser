
#include <criterion/criterion.h>

#include "../../src/LinkedList.h"
#include "../../src/JsonToken.h"
#include "../../src/Json.h"




Test(Json, instanciation_allocates_memory) {
    // given

    // when creating a new instance
    Json * instance = _Json->new("{ \"foo\": 42 }");

    // then an usable memory block should be returned
    cr_assert_not_null(
        instance,
        "Creating a new instance should return a valid memory block"
    );
}


Test(Json, destruction_frees_memory) {
    // given an instance
    Json * instance = _Json->new("{ \"foo\": 42 }");

    // when destroying it
    _Json->delete(& instance);

    // then the memory block should have been freed and set to NULL
    cr_assert_null(
        instance,
        "Destroying the instance should free the memory and set the pointer to NULL"
    );
}


Test(Json, stores_source_string) {
    // given a valid json object
    char * jsonString = "{ \"foo\": \"some text\" }";
    Json * json = _Json->new(jsonString);

    // when requesting the raw string used to build the json object
    char const * rawString = _Json->toString(json);

    // then it should match the source one
    cr_assert_str_eq(
        rawString,
        jsonString,
        "Json objects should store the json-string that was used to build them"
    );
}


Test(Json, parses_tokens) {
    // given a valid json object
    char * jsonString = "{ \"foo\": \"some text\" }";
    Json * json = _Json->new(jsonString);

    // when requesting the parsed tokens
    LinkedList * tokens = _Json->getTokens(json);

    // then there should be some
    cr_assert_not_null(
        tokens,
        "Expected to find some tokens from valid json-string"
    );
}


Test(Json, parses_correct_tokens) {
    // given a valid json object
    char * jsonString = "{ \"foo\": \"some text\" }";
    Json * json = _Json->new(jsonString);
    unsigned int tokenIndex;
    char * expectedTokens[] = {
        "{", "\"foo\"", ":", "\"some text\"", "}"
    };

    // when requesting the parsed tokens
    LinkedList * tokens = _Json->getTokens(json);
    JsonToken * token;

    cr_assert_not_null(tokens);

    // then they should match
    for (tokenIndex = 0; tokenIndex < 5; tokenIndex++) {
        token = _LinkedList->getContent(tokens);

        cr_assert_str_eq(
            _JsonToken->getRawString(token),
            expectedTokens[tokenIndex],
            "Expected to find the token '%s', got %s", _JsonToken->getRawString(token), expectedTokens[tokenIndex] 
        );

        tokens = _LinkedList->nextElement(tokens);
    }
}


#error Checkpoint
Test(Json, rejects_invalid_syntax, .timeout=1) {
    // given some jsons with invalid syntax
    char * jsonStrings[] = {
        "{ \"error\" \"missing colon\" }",
        "{ \"error\" : \"missing comma\" \"error2\" : \"foo\" }",
        "\"error\": \"missing opening curly brace\"}",
        "{ \"error\" : \"missing closing curly braces\""
    };
    Json * jsons[4];
    unsigned int jsonIndex;

    // when creating objects from them
    for (jsonIndex = 0; jsonIndex < 4; jsonIndex++) {
        jsons[jsonIndex] = _Json->new(jsonStrings[jsonIndex]);
    }

    // they no valid instance should be returned
    for (jsonIndex = 0; jsonIndex < 4; jsonIndex++) {
        cr_assert_null(
            jsons[jsonIndex],
            "Didn't expect to get a valid instance from json-string '%s'", jsonStrings[jsonIndex]
        );
    }
}
