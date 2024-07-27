CC=clang
CFLAGS=-Wall -Wextra -fsanitize=undefined
OBJECTS=test_runner.o mf_string.o

.PHONY: run
run: test
	./test

*.o: *.h

test: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o test

.PHONY: clean
clean:
	rm -f test
	rm -f *.o
