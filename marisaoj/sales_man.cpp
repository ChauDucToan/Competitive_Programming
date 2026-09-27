#include <climits>
#include <iostream>

using namespace std;

int n;
int A[10][10];
bool visited[10];
int minCoin = INT_MAX;

void process(int pos, int total, int count) {
  if (count == n) {
    total += A[pos][0];
    if (total < minCoin)
      minCoin = total;
    return;
  }

  if (total > minCoin)
    return;

  // Chose next destinition
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      visited[i] = true;
      process(i, total + A[pos][i], count + 1);
      visited[i] = false;
    }
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }

  visited[0] = true;
  process(0, 0, 1);

  cout << minCoin;
  return 0;
}
