/* gcc gcd_iter.c -o gcd_iter.exe && ./gcd_iter.exe */
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


int gcd_iter(int x, int y) {
  int q;
  assert(y != 0);
  for (;;) {
    q = eu_mod(x, y);
    if (q == 0) return y;
    x = y; y = q;
  }
}


int main() {
  int x, y, g;
  read_input(&x, &y);
  g = gcd_iter(x, y);
  printf("%d\n", g);
}
