#include <stdio.h>

int main() {
  char names[2][5] = {"Gus", "Cris"}; 
  int ages[2] = {25, 30};
  for (int i = 0; i < 2; i++) {
    printf("%s is %d years old\n", names[i], ages[i]);
  }

  return 0;
}