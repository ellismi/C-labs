// Lab 7 - counting polygon square

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define M_PI 3.14159265358979323846
int count = 0;

typedef struct point {
  int x, y;
  int num;
  int u, v;
} POINT;
POINT *p, *a, *b;

bool square(POINT *a, POINT *b, POINT *c) {
  // a b - ostov
  return a->x * (b->y - c->y) + b->x * (c->y - a->y) + c->x * (a->y - b->y) > 0;
}

double angle(POINT *a, POINT *b, POINT *c) {
  POINT q, w;
  // length vector
  q.x = b->x - a->x;
  q.y = b->y - a->y;
  w.x = b->x - c->x;
  w.y = b->y - c->y;
  double ang = 0;
  ang = acos((q.x * w.x + q.y * w.y) /
             (sqrt((q.x * q.x + q.y * q.y) * (w.x * w.x + w.y * w.y)))) *
        180 / M_PI;
  return (180 - ang);
}

sort_baU(POINT *p) { return angle(A) }

int main(int argc, char *argv[]) {
  FILE *in;
  while (--argc) {
    in = fopen(argv[argc], "r");
    if (in == NULL) {
      printf("file 1 don't open !\n");
    }

    // read
    fscanf(in, "%d", &count);
    p = (POINT *)malloc(count * sizeof(POINT));
    a = (POINT *)malloc(sizeof(POINT));
    b = (POINT *)malloc(sizeof(POINT));
    for (int i = 0; i < count; i++) {
      fscanf(in, "%d %d", &p[i].x, &p[i].y);
    }
    fscanf(in, "%d %d", &a->x, &a->y);
    fscanf(in, "%d %d", &b->x, &b->y);
    for (int i = 0; i < count; i++) {
      printf("%d %d\n", p[i].x, p[i].y);
    }
  

  }
  // system("pause");

  return 0;
}