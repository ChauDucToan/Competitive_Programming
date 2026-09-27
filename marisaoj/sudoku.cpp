#include <array>
#include <iostream>

using namespace std;

typedef array<array<int, 9>, 9> Board;

void output(const Board &b) {
  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 9; x++) {
      cout << b[y][x] << " ";
    }
    cout << endl;
  }
}

bool check(const Board &b, int x, int y, int num) {
  for (int i = 0; i < 9; i++) {
    if (b[y][i] == num || b[i][x] == num)
      return false;
  }

  for (int i = 0, idi = y - (y % 3); i < 3; i++) {
    for (int j = 0, idj = x - (x % 3); j < 3; j++) {
      if (b[idi + i][idj + j] == num)
        return false;
    }
  }
  return true;
}

bool process(Board &b, int x = 0, int y = 0) {
  if (y == 9)
    return true;
  if (x == 9)
    return process(b, 0, y + 1);

  if (b[y][x] != 0)
    return process(b, x + 1, y);

  for (int num = 1; num < 10; num++) {
    if (check(b, x, y, num)) {
      b[y][x] = num;

      if (process(b, x + 1, y))
        return true;

      b[y][x] = 0;
    }
  }
  return false;
}

int main() {
  Board b;
  for (int y = 0; y < 9; y++) {
    for (int x = 0; x < 9; x++) {
      cin >> b[y][x];
    }
  }
  process(b);
  output(b);

  return 0;
}
