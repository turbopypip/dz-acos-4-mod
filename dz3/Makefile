CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -O2 -fPIC

ifeq ($(shell uname -s),Darwin)
PROGRAM_LDFLAGS := -Wl,-flat_namespace
PRELOAD_ENV := DYLD_INSERT_LIBRARIES=./libpreload.so DYLD_FORCE_FLAT_NAMESPACE=1
else
PROGRAM_LDFLAGS :=
PRELOAD_ENV := LD_PRELOAD=./libpreload.so
endif

all: program libpreload.so

liboriginal.a: fred.o john.o
	ar rcs $@ $^

liboriginal.so: bill.o sam.o
	$(CC) -shared -o $@ $^ -lm

program: main.o interpose_link.o liboriginal.a liboriginal.so
	$(CC) -o $@ main.o interpose_link.o -L. -loriginal -Wl,-rpath,'$$ORIGIN' -lm $(PROGRAM_LDFLAGS)

libpreload.so: interpose_preload.o
	$(CC) -shared -o $@ $^

run: program
	./program

run_preload: program libpreload.so
	$(PRELOAD_ENV) ./program

clean:
	rm -f *.o liboriginal.a liboriginal.so libpreload.so program

.PHONY: all run run_preload clean
