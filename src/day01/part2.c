#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *file;
  fopen_s(
      &file,
      "C:\\Users\\biel_\\Documents\\projetos\\AOC2025\\src\\day01\\input.txt",
      "r");
  char buffer[1024]; // Buffer for reading lines
  int pivot = 50;
  int count = 0;
  int before;
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    if (buffer[0] == 'L') {
      if (pivot == 0) {
        count--;
      }
      pivot -= atoi(buffer + 1);
      if (pivot <= 0) {
        count += abs(pivot / 100) + 1;
        pivot = ((pivot % 100 + 100) % 100);
      }
    } else {
      pivot += atoi(buffer + 1);
      count += pivot / 100;
      pivot = pivot % 100;
    }
  }
  printf("%d\n", count);
}
