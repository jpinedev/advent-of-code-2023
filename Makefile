PROGRAMS= day1 day2 day3

CC=g++-12
CXXFLAGS=-std=c++20 -O0 -fno-inline -g -Wall -Wextra -Wpedantic -Werror -pedantic-errors -pthread
LDFLAGS=-std=c++20

all: $(PROGRAMS)

main: main.o
	$(CC) $(LDFLAGS) $^ -o $@.out

tests: tests.o

%.o: %.cpp *.hpp Makefile
	$(CC) $(CXXFLAGS) -c $< -o $@

newDay:
	cp ./dayX.cpp ./day$(DAY).cpp
	touch ./inputs/day$(DAY).txt
	sed -i 's/dayX/day$(DAY)/' ./day$(DAY).cpp
	sed -i 's/^PROGRAMS.*$\/& day$(DAY)/g' Makefile
	code ./day$(DAY).cpp
	code ./inputs/day$(DAY).txt

clean:
	rm -rf .vscode/*~ *.o */*.o */*/*.o *.dSYM $(PROGRAMS) *.log
