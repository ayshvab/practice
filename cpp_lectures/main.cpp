#include <cassert>
#include <cstddef>
#include <cstdio>
#include <iostream>

struct foo {
	struct foo_inner {
		char *p;
		short x;
	} inner;
	char c;
};

struct foo2 {
	char *p;
	short x;
	char c;
};

struct foo3 {
	// int flip:1;
	// int nybble:4;
	// int septet:7;
	short s;
	char c;
};

struct foo4 {
	int x;
	char y;
};

int main() {
	std::cout << "sizeof(foo) = " << sizeof(foo) << " bytes" << std::endl;
	std::cout << "sizeof(foo2) = " << sizeof(foo2) << " bytes" << std::endl;
	std::cout << "sizeof(foo3) = " << sizeof(foo3) << " bytes" << std::endl;
	std::cout << "sizeof(foo4) = " << sizeof(foo4) << " bytes" << std::endl;
	return 0;
}

