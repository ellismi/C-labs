// Lab 5 - labirint

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

int heigh = 0, lengh = 0, max = 100000;

typedef struct cell {
  char count;  // symbol
  int steps;
} CELL;

struct cell **labirint;

// do border
char setbound(char b) {
  if (b >= '0' && b <= '9') b = b - '0';
  if (b >= 'A' && b <= 'F') b = b - 'A' + 10;
  return b;
}

// check border
int up(char a) { return a & 0b0001; }
int left(char a) { return a & 0b1000; }
int bottom(char a) { return a & 0b0100; }
int right(char a) { return a & 0b0010; }

void proof(struct cell **a);

void wayback();

int main(int argc, char *argv[]) {
  FILE *in;
  char *maze;
  int c;
  maze = (char *)malloc(100000 * sizeof(char));
  int count = 0;

  if (argc < 2) {
    printf("No arguments\n");
    exit(0);
  }
  while (--argc) {
    in = fopen(argv[1], "r");
    if (in == NULL) {
      printf("file don't open\n");
      exit(0);
    }
    // read
    while (true) {
      c = fgetc(in);
      if (c == '\r') continue;
      if (c == EOF) break;
      if (c == '\n') {
        heigh++;
        continue;
      }
      if (c != '\n' && c != '\r') lengh++;
      maze[lengh - 1] = c;
    }
    maze[10000] = '\0';
    fclose(in);
    heigh++;  // because of eof not \n
    lengh = lengh / heigh;

    // fill labirint
    labirint = (struct cell **)malloc((heigh) * sizeof(struct cell *));
    printf("\n%d", heigh);
    for (int i = 0; i < heigh; i++) {
      labirint[i] = (struct cell *)malloc((lengh) * sizeof(struct cell));
      for (int j = 0; j < lengh; j++) {
        labirint[i][j].count = setbound(maze[count]);
        labirint[i][j].steps = max;
        count++;
      }
    }
  }
  proof(labirint);
  wayback();
  return 0;
}

void proof(struct cell **a) {
  int l = 0;
  int end = false;
  labirint[0][0].steps = 0;
  while (!end) {
    end = 1;
    for (int i = 0; i < heigh; i++)
      for (int j = 0; j < lengh; j++) {
        struct cell *p = &labirint[i][j];
        if (p->steps == l) {
          if (!up(p->count) && labirint[i - 1][j].steps > l)
            labirint[i - 1][j].steps = l + 1;
          if (!right(p->count) && labirint[i][j + 1].steps > l)
            labirint[i][j + 1].steps = l + 1;
          if (!bottom(p->count) && labirint[i + 1][j].steps > l)
            labirint[i + 1][j].steps = l + 1;
          if (!left(p->count) && labirint[i][j - 1].steps > l)
            labirint[i][j - 1].steps = l + 1;
          end = 0;
        }
      }
    l++;
  }
}

void wayback() {
  int x = lengh - 1, y = heigh - 1;
  std::stack<char> Way;
  char s;
  int d = labirint[y][x].steps;
  while (x || y) {
    d--;
    if (y != 0 && !up(labirint[y][x].count) && labirint[y - 1][x].steps == d) {
      s = 0;
      y--;
    } else if (x < lengh - 1 && !right(labirint[y][x].count) &&
               labirint[y][x + 1].steps == d) {
      s = 1;
      x++;
    } else if (y < heigh - 1 && !bottom(labirint[y][x].count) &&
               labirint[y + 1][x].steps == d) {
      s = 2;
      y++;
    } else if (x != 0 && !left(labirint[y][x].count) &&
               labirint[y][x - 1].steps == d) {
      s = 3;
      x--;
    }
    Way.push(s);
  }
  printf("Way: ");
  while (!Way.empty()) {
    s = Way.top();
    switch (s) {
      case 0:
        printf("down");
        break;
      case 1:
        printf("left");
        break;
      case 2:
        printf("up");
        break;
      case 3:
        printf("right");
        break;
      default:
        printf("err");
        break;
    }
    Way.pop();
    if (!Way.empty()) printf(" -- ");
  }
}
