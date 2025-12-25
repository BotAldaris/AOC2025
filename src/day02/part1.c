#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUFFER_SIZE = 4096;

int main() {
  FILE *file = fopen("./src/day02/input.txt", "r");
  if (file == NULL)
    return 1;

  char buf[BUFFER_SIZE + 1];
  char number[BUFFER_SIZE + 1];
  unsigned long long total = 0;

  size_t current_len = fread(buf, 1, BUFFER_SIZE, file);
  int start = 0;
  int pow10[10] = {1,      10,      100,      1000,      10000,
                   100000, 1000000, 10000000, 100000000, 1000000000};

  while (current_len > 0) {
    buf[current_len] = '\0';
    int pos = start;
    int minus_loc = -1, comma_loc = -1;

    for (; pos < (int)current_len; pos++) {
      if (buf[pos] == '-') {
        minus_loc = pos;
        break;
      }
    }

    for (; pos < (int)current_len; pos++) {
      if (buf[pos] == ',') {
        comma_loc = pos;
        break;
      }
    }

    if (minus_loc == -1 || comma_loc == -1) {
      size_t remaining = current_len - start;
      memmove(buf, buf + start, remaining);

      size_t just_read =
          fread(buf + remaining, 1, BUFFER_SIZE - remaining, file);
      current_len = remaining + just_read;
      buf[current_len] = '\0';

      start = 0;
      if (just_read == 0) {
        break;
      }
      continue;
    }

    int len1 = minus_loc - start;
    memcpy(number, buf + start, len1);
    number[len1] = '\0';
    long long first = atoll(number);

    int len2 = comma_loc - (minus_loc + 1);
    memcpy(number, buf + minus_loc + 1, len2);
    number[len2] = '\0';
    long long second = atoll(number);

    for (long long i = first; i <= second; i++) {
      long long n = i;
      int digits = 0;

      while (n > 0) {
        n /= 10;
        digits++;
      }

      if (digits % 2 != 0)
        continue;

      int half = digits / 2;
      long long divisor = pow10[half];

      long long left = i / divisor;
      long long right = i % divisor;

      if (left == right)
        total += i;
    }

    start = comma_loc + 1;
  }
  printf("%llu", total);
  fclose(file);
  return 0;
}