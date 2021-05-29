
#include <criterion/criterion.h>

#include "../../src/JsonToken.h"




Test(JsonToken, rejects_null_string) {
    // given an invalid string address
    char * nullString = NULL;

    // when trying to create a token from it
    JsonToken * token = _JsonToken->new(nullString);

    // then no instance should be returned
    cr_assert_null(
        token,
        "Token shouldn't be created when given a NULL string"
    );
}


Test(JsonToken, accepts_litteral_integer) {
    // given a string with a litteral integer
    char * integer = "-42";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(integer);

    // then a valid instance should be returned
    cr_assert_not_null(
        token,
        "Constructor shouldn't reject litteral \"42\" integer"
    );
}


Test(JsonToken, rejects_invalid_integer) {
    // given a string with an invalid integer notation
    char * invalidFloat = "--42";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(invalidFloat);

    // then no instance should be returned
    cr_assert_null(
        token,
        "Constructor should reject integer with multiple signs"
    );
}


Test(JsonToken, stores_integer_type) {
    // given strings with a litteral integer
    char * integer = "42";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(integer);

    // then the token should have the type integer
    cr_assert_eq(
        _JsonToken->getType(token),
        JSON_TOKEN_INTEGER,
        "Created instance should have the type integer"
    );
}


Test(JsonToken, parses_integer_value) {
    // given a string with a litteral integer
    char * integer = "42";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(integer);

    // then the token should contain the litteral integer value
    cr_assert_eq(
        _JsonToken->asInteger(token),
        42,
        "Created instance should contain the litteral integer value %s", integer
    );
}


Test(JsonToken, accepts_litteral_float) {
    // given a string with a litteral float
    char * number = "42.84";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(number);

    // then a valid instance should be returned
    cr_assert_not_null(
        token,
        "Constructor shouldn't reject litteral \"42.84\" number"
    );
}


Test(JsonToken, rejects_invalid_float) {
    // given a string with an invalid float notation
    char * invalidFloat = "42..84";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(invalidFloat);

    // then no instance should be returned
    cr_assert_null(
        token,
        "Constructor should reject floats with multiple points"
    );
}


Test(JsonToken, destruction_free_memory) {
    // given an instance
    JsonToken * instance = _JsonToken->new("42");

    // when destroying it
    _JsonToken->delete(& instance);

    // then the memory block should have been freed and set to NULL
    cr_assert_null(
        instance,
        "Destroying the instance should free the memory and set the pointer to NULL"
    );
}


Test(JsonToken, stores_float_type) {
    // given strings with a litteral float
    char * number = "-42.84";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(number);

    // then the token should have the type float
    cr_assert_eq(
        _JsonToken->getType(token),
        JSON_TOKEN_FLOAT,
        "Created instance should have the type float"
    );
}


Test(JsonToken, parses_float_value) {
    // given a string with a litteral float
    char * number = "42.84";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(number);

    // then the token should contain the litteral float value
    cr_assert_eq(
        _JsonToken->asFloat(token),
        42.84,
        "Created instance should contain the litteral float value %s", number
    );
}


Test(JsonToken, accepts_litteral_false) {
    // given a string with a litteral false
    char * falsy = "false";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(falsy);

    // then a valid instance should be returned
    cr_assert_not_null(
        token,
        "Constructor shouldn't reject litteral \"false\" boolean"
    );
}


Test(JsonToken, accepts_litteral_true) {
    // given a string with a litteral true
    char * truthy = "true";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(truthy);

    // then a valid instance should be returned
    cr_assert_not_null(
        token,
        "Constructor shouldn't reject litteral \"true\" boolean"
    );
}


Test(JsonToken, stores_boolean_type) {
    // given a string with a litteral false
    char * falsy = "false";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(falsy);

    // then the token should have the type boolean
    cr_assert_eq(
        _JsonToken->getType(token),
        JSON_TOKEN_BOOLEAN,
        "Created instance should have the type boolean"
    );
}


Test(JsonToken, parses_boolean_false_value) {
    // given a string with a litteral false
    char * falsy = "false";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(falsy);

    // then the token should contain the litteral boolean false value
    cr_assert_eq(
        _JsonToken->asBoolean(token),
        0,
        "Created instance should contain the litteral boolean false value (0)" 
    );
}


Test(JsonToken, parses_boolean_true_value) {
    // given a string with a litteral true
    char * truthy = "true";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(truthy);

    // then the token should contain the litteral boolean true value
    cr_assert_eq(
        _JsonToken->asBoolean(token),
        1,
        "Created instance should contain the litteral boolean true value (1)"
    );
}


Test(JsonToken, accepts_operator) {
    // given a list of valid operators
    char * operators[] = { "{", "}", "[", "]", ":", "," };
    JsonToken * token;
    unsigned int operatorIndex;

    // when creating a token from any valid operator
    for (operatorIndex = 0; operatorIndex < 6; operatorIndex++) {
        token = _JsonToken->new(operators[operatorIndex]);

        // then a valid instance should be returned
        cr_assert_not_null(
            token,
            "Constructor should accept operator %s", operators[operatorIndex]
        );
    }
}


Test(JsonToken, stores_operator_type) {
    // given a list of valid operators
    char * operators[] = { "{", "}", "[", "]", ":", "," };
    JsonToken * token;
    unsigned int operatorIndex;

    // when creating a token from any valid operator
    for (operatorIndex = 0; operatorIndex < 6; operatorIndex++) {
        token = _JsonToken->new(operators[operatorIndex]);

        // then the token should contain the operator
        cr_assert_eq(
            _JsonToken->getType(token),
            JSON_TOKEN_OPERATOR,
            "Created instance should have the type operator (\"%s\")", operators[operatorIndex]
        );
    }
}


Test(JsonToken, parses_operator_value) {
    // given a list of valid operators
    char * operatorStrings[] = { "{", "}", "[", "]", ":", "," };
    JsonOperator operatorValues[] = {
        JSON_OPERATOR_OBJECT_START,
        JSON_OPERATOR_OBJECT_END,
        JSON_OPERATOR_ARRAY_START,
        JSON_OPERATOR_ARRAY_END,
        JSON_OPERATOR_COLON,
        JSON_OPERATOR_COMMA,    
    };
    JsonToken * token;
    unsigned int operatorIndex;

    // when creating a token from any valid operator
    for (operatorIndex = 0; operatorIndex < 6; operatorIndex++) {
        token = _JsonToken->new(operatorStrings[operatorIndex]);

        // then the token should contain the operator
        cr_assert_eq(
            _JsonToken->asOperator(token),
            operatorValues[operatorIndex],
            "Created instance should contain the operator %s", operatorStrings[operatorIndex] 
        );
    }
}


Test(JsonToken, rejects_unclosed_string_values) {
    // given an unclosed string
    char * unclosedString = "\"42";
    
    // when creating a token with it
    JsonToken * token = _JsonToken->new(unclosedString);

    // then no instance should be returned
    cr_assert_null(
        token,
        "Token shouldn't be created when given an unclosed string"
    );
}


Test(JsonToken, rejects_unopened_strings) {
    // given an unopened string
    char * openedString = "42\"";
    
    // when creating a token with it
    JsonToken * token = _JsonToken->new(openedString);

    // then no instance should be returned
    cr_assert_null(
        token,
        "Token shouldn't be created when given an unopened string"
    );
}


Test(JsonToken, rejects_unescaped_quote_in_strings) {
    // given a string with unescaped quote
    char * unescapedString = "\"4\"2\"";
    
    // when creating a token with it
    JsonToken * token = _JsonToken->new(unescapedString);

    // then no instance should be returned
    cr_assert_null(
        token,
        "Token shouldn't be created when given a string with unescaped quote"
    );
}


Test(JsonToken, accepts_escaped_quote_in_strings) {
    // given a string with unescaped quote
    char * escapedString = "\"4\\\"2\"";
    
    // when creating a token with it
    JsonToken * token = _JsonToken->new(escapedString);

    // then a valid instance should be returned
    cr_assert_not_null(
        token,
        "Token should be created when given a string with properly escaped quotes"
    );
}


Test(JsonToken, stores_string_type) {
    // given a string with unescaped quote
    char * escapedString = "\"4\\\"2\"";
    
    // when creating a token with it
    JsonToken * token = _JsonToken->new(escapedString);

    // then the token should have the type string
    cr_assert_eq(
        _JsonToken->getType(token),
        JSON_TOKEN_STRING,
        "Created instance should have the type string"
    );
}


Test(JsonToken, parses_string_value) {
    // given a string with escaped quote
    char * escapedString = "\"4\\\"2\"";
    
    // when creating a token with it
    JsonToken * token = _JsonToken->new(escapedString);

    // then the token should contain the string value
    cr_assert_str_eq(
        _JsonToken->asString(token),
        escapedString,
        "Created instance should contain the string [%s]", escapedString 
    );
}


Test(JsonToken, stores_raw_string) {
    // given a valid token-string
    char * rawString = "\"foo\"";

    // when creating a token from it
    JsonToken * token = _JsonToken->new(rawString);

    // then the created instance should contain the raw string
    cr_assert_str_eq(
        _JsonToken->getRawString(token),
        rawString,
        "Created token should store the raw string [%s]", rawString
    );
}
