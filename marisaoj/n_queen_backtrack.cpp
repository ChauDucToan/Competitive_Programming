#include <iostream>
#include <vector>

using namespace std;

bool check(int x, int y, vector<bool> map, int n) {
  int top_b = y - x;
  int bot_b = y + x;
  for (int i = 0; i < n; i++) {
    // Hold Y and run X
    if (map[i * n + y])
      return false;

    // Hold X and run Y
    if (map[n * x + i])
      return false;

    // Left diag
    // y = x + b
    // b = y - x
    // .x.x
    // ..x.
    // ....
    // ....
    // (1, 2)
    // -> top_b = 1
    // -> bot_b = 3
    int diag_y = i + top_b;

    if (diag_y >= 0 && diag_y < n && map[i * n + diag_y])
      return false;

    diag_y = bot_b - i;

    if (diag_y >= 0 && diag_y < n && map[i * n + diag_y])
      return false;
  }

  return true;
}

void output(vector<bool> map, int n) {
  int size = (int)map.size();
  for (int i = 0; i < size; i++) {
    if (i != 0 && i % n == 0) {
      cout << endl;
    }
    if (map[i] == false) {
      cout << ".";
    } else {
      cout << "X";
    }
  }
}

void process(vector<bool> &map, int n, int &counter, int count = 0) {
  if (count == n) {
    counter += 1;
  } else {
    int x = count;
    for (int y = 0; y < n; y++) {
      if (check(x, y, map, n)) {
        map[n * x + y] = true;
        process(map, n, counter, count + 1);
        map[n * x + y] = false;
      }
    }
  }
}

int main() {
  int n;
  int counter = 0;
  cin >> n;
  vector<bool> map(n * n, false);
  process(map, n, counter);
  cout << counter;
  return 0;
}
