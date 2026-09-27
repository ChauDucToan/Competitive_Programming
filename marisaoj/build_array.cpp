#include <iostream>
#include <vector>

using namespace std;

bool check_cond(const vector<vector<int>> &conditions,
                const vector<int> &result) {
  int condition_length = (int)conditions.size();
  for (int i = 0; i < condition_length; i++) {
    if (result[conditions[i][0] - 1] + result[conditions[i][1] - 1] !=
        conditions[i][2])
      return false;
  }
  return true;
}

void build_array(const int &m, int n, int &counter,
                 const vector<vector<int>> &conditions, vector<int> &result) {
  if (n == 0) {
    if (check_cond(conditions, result)) {
      counter++;
    }
    return;
  }

  for (int val = 1; val <= m; val++) {
    result[n - 1] = val;
    build_array(m, n - 1, counter, conditions, result);
  }
}

int main() {
  int counter = 0;
  int n, m, q;
  int i, j, k;
  cin >> n >> m >> q;

  vector<vector<int>> conditions(q, vector<int>(3));
  vector<int> result(n, 0);
  for (int id = 0; id < q; id++) {
    cin >> i >> j >> k;
    vector<int> condition = {i, j, k};
    conditions[id] = condition;
  }

  build_array(m, n, counter, conditions, result);
  cout << counter;

  return 0;
}
