#include <iostream>
#include <string>

using namespace std;

string s;

void output() { cout << s << endl; }

void process(int n, int idx = 0) {
  if (idx == n) {
    output();
  } else
    for (int i = 0; i < 2; i++) {
      s.push_back(static_cast<char>('0' + i));

      process(n, idx + 1);

      s.pop_back();
    }
}

int main() {
  int n;
  cin >> n;
  process(n);
  return 0;
}
