#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *file;
  fopen_s(&file,
          "C:\\Users\\biel_\\Documents\\projetos\\AOC2025\\src\\day1\\.txt",
          "r");
  char buffer[1024]; // Buffer for reading lines
  int pivot = 50;
  int count = 0;
  int before;
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    before = pivot;
    if (buffer[0] == 'L') {
      pivot -= atoi(buffer + 1);
    } else {
      pivot += atoi(buffer + 1);
    }

    if (pivot > 99) {
      count += pivot / 100;
      pivot = pivot % 100;
    } else if (pivot <= 0) {
      count++;
      if (before == 0) {
        count--;
      }
      count += abs(pivot / 100);
      pivot = 100 + pivot % 100;
    }
  }
  printf("%d\n", count);
}
