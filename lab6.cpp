#include <stdio.h>
#include <stdlib.h>
#include <stack>

typedef struct pix {
  int num;
  float x, y;
} PIX;

int count = 0;
int me_ser = 1000;

PIX *pixs;
std::stack<PIX *> HH;  // ^
std::stack<PIX *> BB;  // ✔

int diff(const void *a, const void *b) { return (*(PIX *)b).x - (*(PIX *)a).x; }

// from determinamt
int square(PIX *a, PIX *b, PIX *c) {
  return a->x * (b->y - c->y) + b->x * (c->y - a->y) + c->x * (a->y - b->y) < 0;
}

int main(int argc, char *argv[]) {
  FILE *in;
  char c;
  while (--argc) {
    in = fopen(argv[argc], "r");
    if (in == NULL) {
      printf("file 1 don't open !\n");
    }
    pixs = (PIX *)malloc(sizeof(PIX) * me_ser);
    PIX *p = &pixs[0];

    // read
    while (fscanf(in, "%d %f %f", &p->num, &p->x, &p->y) > 0) {
      count++;
      if (me_ser <= count) {
        me_ser += 10;
        pixs = (PIX *)realloc(pixs, sizeof(PIX) * me_ser);
      }
      p = &pixs[count];
    }
    fclose(in);
    qsort(pixs, count, sizeof(PIX), diff);

    // fuction
    for (int i = 0; i < count; i++) {
      PIX *q, *w, *e = pixs + i;
      while (HH.size() >= 2) {
        w = HH.top();
        HH.pop();
        q = HH.top();
        if (square(q, w, e)) {
          HH.push(w);
          break;
        } else {
          continue;
        }
      }
      HH.push(e);
      while (BB.size() >= 2) {
        w = BB.top();
        BB.pop();
        q = BB.top();
        if (!square(q, w, e)) {
          BB.push(w);
          break;
        } else {
          continue;
        }
      }
      BB.push(e);
    }

    //print 
    printf("Nums of shell:\n");
    HH.pop();
    while (!HH.empty()) {
      printf("%d ", HH.top()->num);
      HH.pop();
    }
    std::stack<PIX *> yBB;
    while (BB.size() > 0) {
      yBB.push(BB.top());
      BB.pop();
    }
    yBB.pop();
    while (!yBB.empty()) {
      printf("%d ", yBB.top()->num);
      yBB.pop();
    }
    printf("\n");
  }
  return 0;
}