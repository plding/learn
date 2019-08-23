CC = gcc
CFLAGS = -std=c99 -Wall -I../src
PROGS = test_zmalloc test_sds test_adlist

all: $(PROGS)

test_zmalloc: test_zmalloc.c ../src/zmalloc.c
	$(CC) $(CFLAGS) -o $@ $^

test_sds: test_sds.c ../src/zmalloc.c ../src/sds.c
	$(CC) $(CFLAGS) -o $@ $^

test_adlist: test_adlist.c ../src/zmalloc.c ../src/adlist.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROGS)
