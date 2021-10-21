#include <bitset>
#include <cmath>
#include <iostream>
using namespace std;

typedef unsigned long int def;

def mpow(def a, def b) {
  def r = a;
  if (b == 0) return 1;
  for (def i = 1; i < b; i++) {
    r *= a;
  }

  return r;
}

int main() {
  def d;
  def less = 0, gret = 0, equa = 0;

  cin >> d;

  if (d == 1) {
    printf("0\n1\n0\n");
    return 0;
  }

  equa = mpow(2, (d - 1) / 2);

  less = 0;
  if (d > 3) less = 1;
  for (def j = 5; j <= d; j++) {
    if ((j + 1) % 2) {
      less += mpow(2, (j - 5) / 2);
    }
    less *= 2;
  }

  gret = mpow(2, (d - 2)) + less;

  printf("%lu\n%lu\n%lu", gret, equa, less);
}