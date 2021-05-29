
CC=gcc
CFLAGS=-ansi -pedantic -Wextra -Werror #-Wall
CFLAGS_TEST=-pedantic -Wextra -Wall -Werror
LDFLAGS=
LDFLAGS_TEST=-lcriterion

SRC_DIR=src
OBJ_DIR=obj

SRC=$(shell find src -type f -name '*.c')
OBJ=$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC:.c=.o))

TESTS_DIR=tests
TESTS_SRC_DIR=$(TESTS_DIR)/src
TESTS_SRC=$(shell find $(TESTS_SRC_DIR) -type f -name '*.c') 
TESTS_OBJ_DIR=$(TESTS_DIR)/obj
TESTS_OBJ=$(subst $(TESTS_SRC_DIR),$(TESTS_OBJ_DIR),$(TESTS_SRC:.c=.o))
TESTS_BIN_DIR=$(TESTS_DIR)/bin
TESTS_BINS=$(subst $(TESTS_OBJ_DIR),$(TESTS_BIN_DIR),$(TESTS_OBJ:.o=))

default: test-binaries

# name rules
library-objects: $(OBJ)
test-objects: $(TESTS_OBJ)
test-binaries: $(OBJ) $(TESTS_BINS)

# register dependencies between tests and library code
#$(TESTS_BINS): $(OBJ)

# compile library objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

# compile test objects
$(TESTS_OBJ_DIR)/%.o: $(TESTS_SRC_DIR)/%.c
	$(CC) $(CFLAGS_TEST) -c $^ -o $@

# compile test binaries
$(TESTS_BIN_DIR)/%: $(TESTS_OBJ_DIR)/%.o
	echo $(OBJ)
	$(CC) $^ $(OBJ) -o $@ $(LDFLAGS_TEST) 

.PHONY: run-tests
run-tests: test-binaries
	$(foreach TEST_BIN,$(TESTS_BINS),./$(TEST_BIN);)
#	$(foreach TEST_BIN,$(TESTS_BINS),./$(TEST_BIN) --verbose;)

.PHONY: diagnotic
diagnostic: test-binaries
	$(foreach TEST_BIN,$(TESTS_BINS),valgrind --quiet ./$(TEST_BIN) --quiet;)
	
.PHONY: clean
clean:
	find . -type f -name '*.o' | xargs rm 2>/dev/null; true

.PHONY: cleanall
cleanall: clean
	find $(TESTS_BIN_DIR) -type f -executable | xargs rm 2>/dev/null; true
