#include <stdio.h>

void moveRight (int *** now) {
  **now = **now + 1;
}

void moveLeft (int *** now) {
  **now = **now - 1;
}

void loop (int *** now) {

}

void increment (int ** now){
  **now = **now + 1;
}

void decrement (int ** now) {
  **now = **now - 1;
}

void print (int ** now) {
  printf("%d\n", **now);
}
void read (int ** now) {
  char c;
  scanf("%c", &c);
  **now = (int) c;
}

void doIt (char string[], int charId, int ** now) {
  char charNow = string[charId];

  switch (charNow) {
    case '+':
      increment(now);
      break;
    case '-':
      decrement(now);
      break;
    case '>':
      moveRight(&now);
      break;
    case '<':
      moveLeft(&now);
      break;
    case '.':
      print(now);
      break;
    case ',':
      read(now);
      break;
    default:
      break;
  }
}

int main (int argc, char *argv[]) {

  char string[] = ".++.>.++.+.";

  int stringLength = sizeof(string) / sizeof(char);

  int dataArray[30000];

  int * now = dataArray;

  int charId; 
  for (charId = 0; charId < stringLength; charId++) {
    char ch = string[charId];
    doIt(string, charId, &now);
  }
}