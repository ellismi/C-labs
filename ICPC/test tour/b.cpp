#include <iostream>
using namespace std;

int main() {
    int n, m, t, s, x, y = 0;

    cin >> n >> m;

    cin >> t >> s;
    y = n / m;
    y += n % m;

    x = t;
    for (int i = 1; i < y; i++){
        t += s;
        x += t;
    }

    cout << x;
    return 0;
}