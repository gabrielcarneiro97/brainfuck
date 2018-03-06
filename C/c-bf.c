#include <stdio.h>
#include <string.h>

#define DATA_LENGHT 30000
#define CHAR_LENGHT 10000

typedef struct s {
  char charArray[CHAR_LENGHT];
  int dataArray[DATA_LENGHT];
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
  bf data = s.data;

  int hasIn = 0;
  int i;
  for (i = beg + 1; i < CHAR_LENGHT; i++) {
    char ch = data.charArray[i];

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

  while (data.dataArray[data.now] > 0) {
    int i2;
    for (i2 = beg + 1; i2 < end; i2++) {
      char ch = data.charArray[i2];
      i2 = doIt(ch, i2, s).index;
    }
  }

  return s;
}

sbf doIt (char ch, int index, sbf s) {
  switch (ch) {
      case '+':
        s.data = increment(s.data);
        return s;
      case '-':
        s.data = decrement(s.data);
        return s;
      case '>':
        s.data = moveRight(s.data);
        return s;
      case '<':
        s.data = moveLeft(s.data);
        return s;
      case '.':
        s.data = print(s.data);
        return s;
      case '[':
        return loop(s);
      default:
        return s;
    }
}

void brainfuck (char * string) {

  int i;
  sbf s;

  strcpy(s.data.charArray, string);

  printf("%s", s.data.charArray);

  for (i = 0; i < CHAR_LENGHT; i++) {
    char ch = string[i];

    i = doIt(ch, i, s).index;
  }
}

int main (int argc, char *argv[]) {
  char * string = "++++++++[ > ++++[ > ++ > +++ > +++ > + < < < < -] > + > + >->> +[ < ] < -] >>.> ---.+++++++..+++.>>.<-.<.+++.------.--------.>> +.> ++.";
  printf("%s\n", string);
}