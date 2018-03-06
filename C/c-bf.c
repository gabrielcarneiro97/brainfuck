#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s {
  char * charArray;
  int dataArray[30000];
  int now;
} bf;

typedef struct s1 {
  bf data;
  int index;
} sbf;

sbf doIt (char ch, int index, sbf s);

bf moveRight (bf data) {
  data.now += 1;
  return data;
}
bf moveLeft (bf data) {
  if (data.now > 0) {
    data.now -= 1;
  }
  return data;
}

bf increment (bf data) {
  data.dataArray[data.now] += 1;
  return data;
}
bf decrement (bf data) {
  if (data.dataArray[data.now] > 0) {
    data.dataArray[data.now] -= 1;
  }
  return data;
}

bf print (bf data) {
  printf("%d", data.dataArray[data.now]);
  return data;
}
bf read (bf data) {
  char c;
  scanf("%c", &c);

  data.dataArray[data.now] = (int) c;
  return data;
}

sbf loop (sbf s) {
  int beg = s.index;
  int end = 0;

  int hasIn = 0;
  int i;
  for (i = beg + 1; i < strlen(s.data.charArray); i++) {
    char ch = s.data.charArray[i];

    if (ch == '[') {
      hasIn += 1;
    } else if (ch == ']') {
      if (hasIn == 0) {
        end = i;
        break;
      } else {
        hasIn -= 1;
      }
    }
  }

  while (s.data.dataArray[s.data.now] > 0) {
    int i2;
    for (i2 = beg + 1; i2 < end; i2++) {
      char ch = s.data.charArray[i2];
      
      s = doIt(ch, i2, s);
      i2 = s.index;
    }
  }

  s.index = end;
  return s;
}

sbf doIt (char ch, int index, sbf s) {
  switch (ch) {
      case '+':
        s.data = increment(s.data);
        s.index = index;
        return s;
      case '-':
        s.data = decrement(s.data);
        s.index = index;
        return s;
      case '>':
        s.data = moveRight(s.data);
        s.index = index;
        return s;
      case '<':
        s.data = moveLeft(s.data);
        s.index = index;
        return s;
      case '.':
        s.data = print(s.data);
        s.index = index;
        return s;
      case '[':
        return loop(s);
      default:
        s.index = index;
        return s;
    }
}

void brainfuck (char * string) {

  int i;
  sbf s;

  s.data.charArray = (char *) malloc(strlen(string));

  strcpy(s.data.charArray, string);

  printf("%s", s.data.charArray);
  

  for (i = 0; i < strlen(string); i++) {
    char ch = s.data.charArray[i];

    s = doIt(ch, i, s);
    i = s.index;

  }
}

int main (int argc, char *argv[]) {
  char string[] = "+++[>++++<-]>.";

  brainfuck(string);
}