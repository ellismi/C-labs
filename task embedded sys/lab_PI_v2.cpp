#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

// алгоритм основан на BBP formula для вычисления N-ой цифры числа пи
using namespace std;

int main() {
  // точность числа пи
  const int n = 1500;

  // длина массива для вычисления числа пи
  const int N = n * 10 / 3;

  // само число
  string PI = "";

  // перенос вычислений и сумма
  // (нужно для вычисления N-ой цифры числа пи)
  int carry = 0;
  int sum = 0;

  // массив для промежуточных вычислений
  int tabs[N];

  // подсчет количества неправильынх цифр при переполнении (см ниже)
  int wrongnum = 0;

  // вывод
  ofstream out;
  out.open("/tmp/pi.txt", ios_base::trunc);

  auto start = std::chrono::steady_clock::now();
  // инициализация
  for (int i = 0; i < N; i++) {
    tabs[i] = 2;
  }

  for (int i = 0; i < n; i++) {
    carry = 0;
    sum = 0;
    for (int j = N - 1; j >= 0; j--) {
      tabs[j] *= 10;
      sum = tabs[j] + carry;
      tabs[j] = sum % (j * 2 + 1);
      carry = sum / (j * 2 + 1);
      carry *= j;
    }
    tabs[0] = sum % 10;
    int q = sum / 10;
    // проверка на переполнение, так как вычисленное число
    // может быть больше 10, а вычисляется N-ая цифра числа пи
    switch (q) {
      case 9:
        wrongnum++;
        break;
      case 10:
        q = 0;
        // в случае переполнения инкрементируются предыдущие цифры
        for (int k = 1; k <= wrongnum; k++) {
          char posnum = PI[i - k];
          (posnum == '9') ? posnum = '0' : posnum++;
          PI[i - k] = posnum;
        }
        wrongnum = 1;
        break;
      default:
        wrongnum = 1;
        break;
    }
    PI += to_string(q);
  }

  PI.insert(1, ".");

  auto end = std::chrono::steady_clock::now();

  // запись
  out << PI;
  out.close();

  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  cout << "The time: " << time.count() << " ms\n";

  return 0;
}