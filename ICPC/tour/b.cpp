// временное решение для выявления закономерности (brute force)
#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

const int DSIZE = 8;


typedef unsigned long int def;

def mirror(def v, int size) {
  def d = 0;
  for (def i = 0; i < size; i++) {
    // int b = (v >> i) & 1;
    def b = (v >> (size - i - 1)) & 1;
    //cout << b;

    d = d | (((v >> (size - i - 1)) & 1) << i);

  }

  return d;
}

void calc(def d) {
  def less = 0, gret = 0, equa = 0;

  def start = pow(2, d-1);
  def end = start*2-1;

  for (def i = start; i <= end; i++) {
    def m = mirror(i, d);
    // std::cout << std::bitset<DSIZE>(i) << " / " << std::bitset<DSIZE>(m) << endl;
    if (i > m) gret++;
    if (i < m) less++;
    if (i == m) equa++;
  }

  //cout << "g: " << gret << " e: " << equa << " l: " << less << "\n";
  def e = pow(2, (d - 1) / 2);
  // def g = pow(2, (d - 2));

  // int last = 0;
  // for(int j = 1; j <= d; j++) {
  //   if (j == 1) continue;
  //   if (j %2) g *= 2;
  //   else g++;
  // }
  // g = gret;
  // for(int j = 0; j < 4; j++) {
  // if (g % 2) g--;
  // g /= 2;
  // }

  // def l = pow(2, (d - 1) / 2);
  // def l = pow(2, d - 4) * (d % 2);

  def l = 0;
  if (d > 3) l = 1;
  for (int j = 5; j <= d; j++) {
    if ((j + 1) % 2) {
        l += pow(2, (j-5)/2);
    }
    l *= 2;
    // if
  }

  def g = pow(2, (d - 2)) + l;

  printf("(%4lu) g: %10lu (%4lu)(%6lu) e: %10lu (%5lu) l: %10lu (%4lu)\n", d, gret, g, gret - g, equa, e, less, l);

}

int main() {

  for(int i=1; i<50; i++){
      calc(i);
  }

}