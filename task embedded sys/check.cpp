#include <fstream>
#include <iostream>
#include <string>

// для проверки после запуска
using namespace std;

int main() {
  ifstream rpi;
  rpi.open("rpi.txt");
  ifstream mpi;
  mpi.open("pi2.txt");
  string rPI = "";
  string wPI = "";
  rpi >> rPI;
  mpi >> wPI;
  rpi.close();
  mpi.close();

  cout << rPI.compare(wPI) << endl;
  return 0;
}