LIB_NAME=data_structures
LIB_TARGET_DEBUG=build/lib$(LIB_NAME).a

CC=gcc
CFLAGS=-Wall -Wextra -std=c11
CFLAGS_COVERAGE=-fprofile-arcs -ftest-coverage
CFLAGS_DEBUG=-g -Og -DDEBUG
INC_FLAGS_DEBUG=-I./tests/src -I./src
LDFLAGS_DEBUG=-L./build -l$(LIB_NAME)

LIB_SOURCES=$(wildcard src/*.c)
LIB_OBJECTS_DEBUG=$(patsubst src/%.c,build/%.o,$(LIB_SOURCES))

TESTS_SOURCES=$(wildcard tests/src/test_*.c)
TESTS_BINARIES=$(patsubst tests/src/test_%.c, tests/bin/test_%, $(TESTS_SOURCES))
TESTS_OBJECTS=$(patsubst tests/src/test_%.c, tests/build/test_%.o, $(TESTS_SOURCES))

all:run
build:$(TESTS_BINARIES)
build_lib:$(LIB_TARGET_DEBUG)

#lib objects debug
build/%.o:src/%.c src/%.h
	@mkdir -p ./build
	$(CC) -c -o $@ $(CFLAGS) $(CFLAGS_DEBUG) $(CFLAGS_COVERAGE) $<

#lib target debug
$(LIB_TARGET_DEBUG): $(LIB_OBJECTS_DEBUG)
	ar -rcs $(LIB_TARGET_DEBUG) $(LIB_OBJECTS_DEBUG)
	ranlib $(LIB_TARGET_DEBUG)

#tests objects
tests/build/test_%.o:tests/src/test_%.c
	@mkdir -p ./tests/build
	$(CC) -c -o $@ $(CFLAGS) $(CFLAGS_DEBUG) $(CFLAGS_COVERAGE) $(INC_FLAGS_DEBUG) $<

#tests binaries
tests/bin/test_%:tests/build/test_%.o $(LIB_TARGET_DEBUG)
	@mkdir -p ./tests/bin
	$(CC) -o $@ $< $(LDFLAGS_DEBUG) $(CFLAGS_COVERAGE) $(INC_FLAGS_DEBUG)

run:$(TESTS_BINARIES)
	./scripts/runtests.sh ./tests/bin

memcheck: $(TESTS_BINARIES)
	./scripts/runtests.sh ./tests/bin memcheck

report: run
	gcov $(TESTS_OBJECTS)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage
	./scripts/http_server.sh start 
clean:
	rm -rf tests/build
	rm -rf tests/bin
	rm -rf build
	rm -rf coverage
	rm -rf *.info
	rm -rf *.gcov
	./scripts/http_server.sh stop
	
.PHONY:all clean
.PRECIOUS:tests/build/test_%.o