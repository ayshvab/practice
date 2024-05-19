/* gcc contfrac.c -o contfrac.exe && ./contfrac.exe */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void read_input(int* a, int* b) {
  int res;
  /* printf("input a and b: "); */
  /* fflush(stdout); */
  res = scanf("%d%d", a, b);
  if (res != 2 || *b == 0) {
    printf("Error: input invalid, expect any a and b != 0");
    abort();
  }
}

int iabs(int x) { return (x < 0) ? -x : x; }

int eu_mod(int x, int y) {
  int r;
  assert(y != 0);
  r = x % y;
  if (r < 0) r += iabs(y);
  return r;
}

int eu_div(int x, int y) {
  int r = x / y;
  if (x < 0) {
    r += (-1);
  }
  return r;
}

void contfrac(int x, int y) {
  int q, r;
  assert(y != 0);
  for (;;) {
    q = eu_div(x, y);
    r = eu_mod(x, y);
    printf("%d ", q);
    if (r == 0) break;
    x = y; y = r;
  }
  printf("\n");
}

int main() {
  int x, y;
  read_input(&x, &y);
  contfrac(x, y);
}
