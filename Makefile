CFLAGS = -Wall -Og -g -I./src
TEST_CFLAGS = -I./tests/src


LIB_SOURCES = $(wildcard src/*.c)
LIB_OBJECTS = $(patsubst src/%.c,build/%.o,$(LIB_SOURCES))
TEST_SOURCES = $(wildcard tests/src/*.c)
TEST_OBJECTS = $(patsubst tests/src/%.c,tests/build/%.o,$(TEST_SOURCES))
TEST_BINS = $(patsubst tests/src/%.c,tests/bin/%,$(TEST_SOURCES))

test: build
	@bash ./tests/runtests.sh tests-only

build: $(LIB_OBJECTS) $(TEST_BINS)

memcheck: $(LIB_OBJECTS) $(TEST_BINS)
	@bash ./tests/runtests.sh

build/%.o: src/%.c src/*.h
	@mkdir -p build
	gcc -c $(CFLAGS) $< -o $@

tests/bin/test_%:tests/build/test_%.o $(LIB_OBJECTS)
	@mkdir -p tests/bin
	gcc $(CFLAGS) $(TEST_CFLAGS) $^ -o $@

tests/build/test_%.o: tests/src/test_%.c
	@mkdir -p tests/build
	gcc -c $(CFLAGS) $(TEST_CFLAGS) $< -o $@

clean:
	@rm -rf build
	@rm -rf bin
	@rm -rf tests/build
	@rm -rf tests/bin

.PRECIOUS: tests/build/test_%.o
.PHONY: clean test memcheck build