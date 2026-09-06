#include <iostream>
#include <vector>

using namespace std;

void process(const vector<int> &m, int &best, int x = 0, int y = 0,
             int val = 0) {
  val += m[4 * x + y];
  if (x == 3 && y == 3) {
    best = max(best, val);
    return;
  }

  if (x + 1 < 4)
    process(m, best, x + 1, y, val);
  if (y + 1 < 4)
    process(m, best, x, y + 1, val);
}

int main() {
  int best = 0;
  vector<int> map(16);

  for (int i = 0; i < 16; i++) {
    cin >> map[i];
  }

  process(map, best);
  cout << best;

  return 0;
}
