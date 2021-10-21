#include <fstream>
#include <iostream>
#include <string>

// Мощность алфавита
#define alf 26

using namespace std;

// Вывод
ofstream output;

// Преобразование к числу
inline int normLower(int a) { return a - 'a'; }
inline int normUpper(int a) { return a - 'A'; };

// Шифрование символа
inline int encNum(int m, int y) {
  return isalpha(m) ? (islower(m) ? (((normLower(m) + normLower(y)) % alf) + 'a')
  : (((normUpper(m) + normUpper(y)) % alf) + 'A')) : m;
}

// Расшифрование символа
inline int decNum(int c, int y) {
  return isalpha(c) ? (islower(c) ? (((alf + normLower(c) - normLower(y)) % alf) + 'a')
  : (((alf + normUpper(c) - normUpper(y)) % alf) + 'A')) : c;
}

// Шифрование ввода
void enc(string in, string key) {
  int len = key.length();
  for (int i = 0; i < in.length(); i++) {
    output << (char)encNum(in[i], key[i % len]);
  }
}

// Расшифрование ввода
void dec(string in, string key) {
  int len = key.length();
  for (int i = 0; i < in.length(); i++) {
    output << (char)decNum(in[i], key[i % len]);
  }
}

int main(int ac, char *av[]) {
  // Способ обработки
  char mode = av[1][1];

  // Help
  if (mode == 'h') {
    cout << "Usage: Gamming.exe option input_file key_file [output_file]"
         << endl
         << "Option:" << endl
         << "  -h Display this information" << endl
         << "  -e Encode input file using key file of gamma" << endl
         << "  -d Decode input file using key file of gamma" << endl;
    return 0;
  }

  // Проверка аргументов
  if (ac < 4) {
    cout << "Need more arguments" << endl;
    return 0;
  }

  // Ввод и ключ
  ifstream input(av[2]);
  ifstream key(av[3]);

  // Проверка на открытие ввода и ключа
  if (!input.is_open()) {
    cout << "Input file don't open" << endl;
    return 0;
  }
  if (!key.is_open()) {
    cout << "Key file don't open" << endl;
    return 0;
  }

  // Проверка на открытие файла вывода
  if (ac > 4) {
    output.open(av[4], ios_base::out | ios_base::trunc);
    if (!output.is_open()) {
      cout << "Output file don't open" << endl;
      return 0;
    }
  } else {
    // или его создание
    output.open("out.txt", ios_base::out | ios_base::trunc);
    if (!output.is_open()) {
      cout << "Output file don't open" << endl;
      return 0;
    }
  }

  // Чтение из файла открытого текста и ключа
  string str{std::istreambuf_iterator<char>(input),
             std::istreambuf_iterator<char>()};
  string gamma{std::istreambuf_iterator<char>(key),
               std::istreambuf_iterator<char>()};

  // Закрытие файлов
  input.close();
  key.close();

  // Выбор способа обработки ввода
  switch (mode) {
    // Зашифровка
    case 'e':
      enc(string(str), string(gamma));
      break;
    // Расшифровка
    case 'd':
      dec(string(str), string(gamma));
      break;
    // Если ничего нет из вышеперечисленного
    default:
      cout << "Wrong usage of command!" << endl;
      break;
  }

  // Закрытие файла вывода
  output.close();

  cout << "Done!" << endl;

  return 0;
}