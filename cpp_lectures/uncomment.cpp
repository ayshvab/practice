// $ g++ --no-exceptions uncomment.cpp -o uncomment
// $ ./uncomment
//
#include <cstdio>
#include <iostream>

// Task
// A C program with comments of the from /* comment */ is given.
// You need to write a C++ program that removes all comments from the text of
// the given program

void eat_comment(FILE *in) {
  while (!feof(in) && !ferror(in)) {
    auto c = static_cast<unsigned char>(fgetc(in));
    std::cout << " __c__ " << c << std::endl;
    if (c == '*') {
      auto next = static_cast<unsigned char>(fgetc(in));

      std::cout << "__next__ " << next << std::endl;
      if (next == '/') {
        break;
      }
    }
  }
}

int main(int argc, char **argv) {
  FILE *in;
  if (argc == 1) {
    in = stdin;
  } else if (argc == 2) {
    in = fopen(argv[1], "r");
    if (in == NULL) {
      perror("fopen");
      return 0;
    }
  } else {
    std::cerr << "Usage: "
                 "uncomment program.c"
              << std::endl;
    return 0;
  }

  while (!feof(in) && !ferror(in)) {
    auto c = static_cast<unsigned char>(fgetc(in));
    if (c == '/') {
      auto next = static_cast<unsigned char>(fgetc(in));
      if (next == '*') {
        eat_comment(in);
      } else {
        ungetc(next, in);
      }
    } else if (!feof(in) && !ferror(in)) {
      std::cout << c;
    }
  }
}
