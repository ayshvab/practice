#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void read_input(int* a, int* b) {
  int res;
  printf("input a and b: ");
  fflush(stdout);
  res = scanf("%d%d", a, b);
  if (res != 2 || *b == 0) {
    printf("Error: input invalid, expect any a and b != 0");
    abort();
  }
}

int main() {
  int a, b, p, q;
  read_input(&a, &b);
  assert(b != 0);
  p = a / b; q = a % b;
  printf("p = %d, q = %d\n", p, q);
}
