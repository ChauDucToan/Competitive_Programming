#include <iostream>

using namespace std;

void output(const bool out[][21], int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << out[i][j] << " ";
    }
    cout << endl;
  }
}

bool check(const bool out[][21], const int A[20][20], int i, int j) {
  int count = 0;

  for (int y = -1; y < 2; y++) {
    for (int x = -1; x < 2; x++) {
      if (i + y < 0 || j + x < 0 || (y == 0 && x == 0))
        continue;
      if (out[i + y][j + x])
        count++;
    }
  }

  return count == A[i][j];
}

void process(bool out[][21], int A[20][20], const int &n, const int &m,
             int i = 0, int j = 0) {
  if (i == n) {
    bool valid = true;
    for (int y = 0; y < n && valid; y++) {
      for (int x = 0; x < m; x++) {
        if (!check(out, A, y, x)) {
          valid = false;
          break;
        }
      }
    }

    if (valid)
      output(out, n, m);

    return;
  }

  if (j == m) {
    process(out, A, n, m, i + 1, 0);
    return;
  }

  for (int b = 0; b <= 1; b++) {
    out[i][j] = b;

    if (i >= 1 && j >= 1 && !check(out, A, i - 1, j - 1))
      continue;

    process(out, A, n, m, i, j + 1);
  }
}

int main() {
  int n, m;
  int A[20][20];
  bool out[21][21];
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 21; j++) {
      out[i][j] = 0;
    }
  }
  process(out, A, n, m);
  return 0;
}
