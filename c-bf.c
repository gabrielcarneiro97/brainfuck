#include <stdio.h>

int * moveRight(int *now) {
  now = now + 1;
  return now;
}

int * moveLeft(int *now) {
  now = now - 1;
  return now;
}

int * increment(int *now) {
  printf("%d\n", *now);
  *now = *now + 1;
  return now;
}

int * decrement(int *now) {
  *now = *now - 1;
  return now;
}

int * loop(int *now) {
}

int * print(int *now) {
  printf("%d\n", *now);
}

int * read(int *now) {
  char c;
  scanf("%c", &c);
  *now = (int) c;

  return now;
}

int * doIt (char string[], int charId, int * now) {
  char charNow = string[charId];

  switch (charNow) {
    case '+':
      now = increment(now);
      break;
    case '-':
      now = decrement(now);
      break;
    case '>':
      now = moveRight(now);
      break;
    case '<':
      now = moveLeft(now);
      break;
    case '.':
      now = print(now);
      break;
    case ',':
      now = read(now);
      break;
    default:
      break;
  }

  return now;
}

int main (int argc, char *argv[]) {

  char string[] = ".++.>.";

  int stringLength = sizeof(string) / sizeof(char);

  int dataArray[30000];

  int * now = dataArray;

  int charId;
  for (charId = 0; charId < stringLength; charId++) {
    char ch = string[charId];
    printf("%d\n", *now);
    now = doIt(string, charId, now);
  }
}