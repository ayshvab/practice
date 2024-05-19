// gcc gcd.c -o gcd.exe && ./gcd.exe
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

// int gcd(int x, int y) {
//   int q;
//   assert(y != 0);
//   q = x % y;
//   if (q == 0)
//     return y;
//   return gcd(y, q);
// }

// Problem
// In C % defines as    assert(a == (a / b) * b + (a % b));
// a = 14, b = -8
// (14 / -8) * (-8) + (14 % -8)
// (-1) * (-8) + (+6)
// 8 + 6 = 14

// Euclid div defined as
// a = q * b + r, 0 <= r < |b|

// Define own divide by mod

int iabs(int x) { return (x < 0) ? -x : x; }

int eu_mod(int x, int y) {
  assert(y != 0);
  int r = x % y;
  if (r < 0) r += iabs(y);
  return r;
}

int gcd(int x, int y) {
  assert(y != 0);
  int q = eu_mod(x, y);
  if (q == 0)
    return y;
  return gcd(y, q);
}

int main() {
  int x, y, g;
  read_input(&x, &y);
  g = gcd(x, y);
  printf("gcd(%d, %d)=%d\n", x, y, g);
}
