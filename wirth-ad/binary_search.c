// gcc binary_search.c -o binary_search.exe && ./binary_search.exe
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))

typedef int32_t b32;

struct binary_search_result {
  b32 found;
  ssize_t index;
};

struct binary_search_result binary_search(int what, int *data, ssize_t len) {
  struct binary_search_result r = {0};
  ssize_t left = 0;
  ssize_t m = 0;
  ssize_t right = len;
  while (left < right) {
    m = (left + right) / 2;
    if (data[m] < what) {
      left = m + 1;
    } else {
      right = m;
    }
  }
  r.index = right;
  if (right < len && data[right] == what) {
    r.found = 1;
  }
  return r;
}

struct binary_search_result binary_search_string(char *what, char **data,
                                                 ssize_t len) {
  struct binary_search_result r = {0};
  ssize_t left = 0; // Ak: 0 <= k < L: (a[k] < what)
  ssize_t m = 0;
  ssize_t right = len; // Ak: right <= k < len : (a[k] >= what)
  while (left < right) {
    m = (left + right) / 2;
    ssize_t i = 0;
    while (what[i] != 0 && (what[i] == data[m][i]))
      i++;
    if (data[m][i] < what[i]) {
      left = m + 1;
    } else {
      right = m;
    }
  }
  r.index = right;
  if (right < len) {
    ssize_t i = 0;
    while (what[i] != 0 && (what[i] == data[right][i]))
      i++;
    r.found = what[i] == data[right][i];
  }
  return r;
}

void test_binary_search_empty_array() {
  int data[0];
  int what = 10;
  struct binary_search_result result =
      binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Empty array test (binary_search) passed\n");
}

void test_binary_search_single_element() {
  int data[] = {5};
  int what;
  struct binary_search_result result;

  what = 5;
  result = binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 1);
  assert(result.index == 0);
  printf("Single element (equal) test (binary_search) passed\n");

  what = 3;
  result = binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Single element (less) test (binary_search) passed\n");

  what = 7;
  result = binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Single element (greater) test (binary_search) passed\n");
}

void test_binary_search_sorted_array_found() {
  int data[] = {1, 3, 5, 7, 9};
  int what;
  struct binary_search_result result;

  what = 5;
  result = binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 1);
  assert(result.index == 2);
  printf("Sorted array (middle) test (binary_search) passed\n");

  what = 1;
  result = binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 1);
  assert(result.index == 0);
  printf("Sorted array (first) test (binary_search) passed\n");

  what = 9;
  result = binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 1);
  assert(result.index == 4);
  printf("Sorted array (last) test (binary_search) passed\n");
}

void test_binary_search_sorted_array_not_found() {
  int data[] = {1, 3, 5, 7, 9};
  int what;
  struct binary_search_result result;

  what = 0;
  result = binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Sorted array (less than all) test (binary_search) passed\n");

  what = 10;
  result = binary_search(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Sorted array (greater than all) test (binary_search) passed\n");
}

// Similar test cases for binary_search_string can be implemented here

void test_binary_search_string_empty_string() {
  char *data[] = {"apple", "banana", "cherry"};
  char *what = "";
  struct binary_search_result result =
      binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Empty string test (binary_search_string) passed\n");
}

void test_binary_search_string_single_element() {
  char *data[] = {"apple"};
  char *what;

  what = "apple";
  struct binary_search_result result =
      binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 1);
  assert(result.index == 0);
  printf("Single element (match) test (binary_search_string) passed\n");

  what = "app";
  result = binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf(
      "Single element (shorter prefix) test (binary_search_string) passed\n");
}

void test_binary_search_string_sorted_array_found() {
  char *data[] = {"apple", "banana", "cherry", "mango"};
  char *what;

  what = "banana";
  struct binary_search_result result =
      binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 1);
  assert(result.index == 1);
  printf("Sorted array (exact match) test (binary_search_string) passed\n");

  what = "app";
  result = binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Sorted array (prefix match) test (binary_search_string) passed\n");
}

void test_binary_search_string_sorted_array_not_found() {
  char *data[] = {"apple", "banana", "cherry", "mango"};
  char *what;

  what = "apricot";
  struct binary_search_result result =
      binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Sorted array (less than all) test (binary_search_string) passed\n");

  what = "melon";
  result = binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf(
      "Sorted array (greater than all) test (binary_search_string) passed\n");

  char *data_with_empty[] = {"", "apple", "banana"};
  what = "orange";
  result = binary_search_string(what, data_with_empty,
                                ARRAY_LENGTH(data_with_empty));
  assert(result.found == 0);
  printf("Sorted array (empty string) test (binary_search_string) passed\n");
}

void test_binary_search_string_special_chars() {
  char *data[] = {"alpha!", "beta#", "gamma$"};
  char *what = "beta#";
  struct binary_search_result result =
      binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 1);
  assert(result.index == 1);
  printf("Special characters test (binary_search_string) passed\n");

  what = "beta!"; // Different special character
  result = binary_search_string(what, data, ARRAY_LENGTH(data));
  assert(result.found == 0);
  printf("Special characters (not exact match) test (binary_search_string) "
         "passed\n");
}

int main() {
  printf("Testing binary_search function:\n");
  test_binary_search_empty_array();
  test_binary_search_single_element();
  test_binary_search_sorted_array_found();
  test_binary_search_sorted_array_not_found();

  test_binary_search_string_empty_string();
  test_binary_search_sorted_array_not_found();
  test_binary_search_string_empty_string();
  test_binary_search_string_single_element();
  test_binary_search_string_sorted_array_found();
  test_binary_search_string_sorted_array_not_found();
  test_binary_search_string_special_chars();

  printf("All tests passed!\n");
  return 0;
}
