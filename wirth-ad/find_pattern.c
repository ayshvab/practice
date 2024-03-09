// gcc find_pattern.c -o find_pattern.exe && ./find_pattern.exe
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
#define STR_LENGTH(x) ((sizeof(x) / sizeof(x[0])) - 1)

typedef int32_t b32;
typedef ssize_t isize;

typedef struct find_pattern_result {
  isize index;
  b32 found;
} find_pattern_result;

// Find first pattern matching
find_pattern_result find_pattern(char *text, isize text_len, char *pattern,
                                 isize pattern_len) {
  find_pattern_result result = {};
  isize text_i = 0;
  isize pattern_j = 0;
  if (text_len == 0) {
    result.found = 0;
    return result;
  }
  if (pattern_len == 0) {
    result.found = 1;
    return result;
  }
  //
  // Possible positions in text (text_i) to start pattern matching
  // text_i: 0 <= text_i < text_len - pattern_len
  //
  // Found matching is
  // is_match(i) = All j: 0 <= j < pattern_len: pattern[j] == text[i+j]
  //
  // This is first found matching
  // is_first_match(i) = All k: 0 <= k < i: !is_match(k)
  //
  while (1) {
    if (text_i <= (text_len - pattern_len) && (pattern_j < pattern_len) &&
        (pattern[pattern_j] == text[text_i + pattern_j])) {
      pattern_j++;
    } else if (text_i <= (text_len - pattern_len) && (pattern_j < pattern_len)) {
      pattern_j = 0;
      text_i++;
    } else
      break;
  }
  // Simpler ?
  // while (text_i <= (text_len - pattern_len) && (pattern_j < pattern_len))  {
  //   if (pattern[pattern_j] == text[text_i + pattern_j]) {
  //     pattern_j++;
  //   } else {
  //     text_i++;
  //     pattern_j = 0;
  //   }
  // }
  result.index = text_i;
  result.found = text_i <= (text_len - pattern_len);
  return result;
}

void test_find_pattern_empty_text() {
  char *text = "";
  char *pattern = "abc";
  find_pattern_result result = find_pattern(text, strlen(text), pattern, strlen(pattern));
  assert(result.found == 0);
  printf("Empty text test (find_pattern) passed\n");
}

void test_find_pattern_empty_pattern() {
  char *text = "hello world";
  char *pattern = "";
  find_pattern_result result = find_pattern(text, strlen(text), pattern, strlen(pattern));
  assert(result.found == 1);  // Empty pattern always matches at index 0
  assert(result.index == 0);
  printf("Empty pattern test (find_pattern) passed\n");
}

void test_find_pattern_exact_match() {
  char *text = "hello world";
  char *pattern = "world";
  find_pattern_result result = find_pattern(text, strlen(text), pattern, strlen(pattern));
  assert(result.found == 1);
  assert(result.index == 6);
  printf("Exact match test (find_pattern) passed\n");
}

void test_find_pattern_no_match() {
  char *text = "hello world";
  char *pattern = "apple";
  find_pattern_result result = find_pattern(text, strlen(text), pattern, strlen(pattern));
  assert(result.found == 0);
  printf("No match test (find_pattern) passed\n");
}

void test_find_pattern_simple_match() {
  char *text = "abcababcabca";
  char *pattern = "aba";
  find_pattern_result result;

  result = find_pattern(text, strlen(text), pattern, strlen(pattern));
  assert(result.found == 1);
  assert(result.index == 3);

  text = "abcababcabca";
  pattern = "abcab";
  result = find_pattern(text, strlen(text), pattern, strlen(pattern));
  assert(result.found == 1);
  assert(result.index == 0);

  printf("Simple Match test (find_pattern) passed\n");
}

int main() {
  printf("Testing find_pattern function:\n");
  test_find_pattern_empty_text();
  test_find_pattern_empty_pattern();
  test_find_pattern_exact_match();
  test_find_pattern_no_match();
  test_find_pattern_simple_match();
  printf("All tests passed!\n");
  return 0;
}
