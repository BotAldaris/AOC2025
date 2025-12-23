#include <stdio.h>
#include <stdlib.h>

int get_number(char buffer[1024]);
int main() {
  FILE *file;
  fopen_s(&file, "./src/day01/input.txt", "r");
  char buffer[1024]; // Buffer for reading lines
  int pivot = 50;
  int count = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    if (buffer[0] == 'L') {
      pivot -= atoi(buffer + 1);
    } else if (buffer[0] == 'R') {
      pivot += atoi(buffer + 1);
    }
    if (pivot > 99) {
      pivot = pivot % 100;
    } else if (pivot < 0) {
      pivot = pivot % 100;
      if (pivot != 0) {
        pivot += 100;
      }
    }
    if (pivot == 0) {
      count += 1;
    }
  }
  fclose(file);
  printf("%d\n", count);
}
