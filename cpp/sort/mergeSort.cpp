#include <algorithm>
#include <chrono>
#include <climits>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace std::chrono;

vector<int> sort(vector<int>& arr, int startIndex, int endIndex) {
  if (endIndex - startIndex == 0) {
    return vector<int>();
  }
  if (endIndex - startIndex == 1) {
    return vector<int>{arr[startIndex]};
  }

  int middleIndex = (startIndex + endIndex) / 2;

  auto left = sort(arr, startIndex, middleIndex);
  auto right = sort(arr, middleIndex, endIndex);

  auto merge = [&]() -> vector<int> {
    vector<int> ret;

    int i = 0, j = 0;

    while (i < left.size() || j < right.size()) {
      if (i == left.size()) {
        ret.insert(ret.end(), right.begin() + j, right.end());
        break;
      }
      if (j == right.size()) {
        ret.insert(ret.end(), left.begin() + i, left.end());
        break;
      }

      if (left[i] > right[j]) {
        ret.push_back(right[j]);
        ++j;
      } else if (left[i] == right[j]) {
        ret.insert(ret.end(), {left[i], right[j]});
        ++i;
        ++j;
      } else {
        ret.push_back(left[i]);
        ++i;
      }
    }
    return ret;
  };

  return merge();
}

void sort(vector<int>& arr) {
  auto ret = sort(arr, 0, arr.size());
  arr = move(ret);
}

int main() {
  vector<int> input = {
      3,    1,    5,   9,    0,   10,  5,    32,  -1,  -20,  239, 583,
      6,    3,    54,  53,   38,  34,  653,  75,  345, 7576, 45,  27,
      4564, 8765, 24,  1,    435, 564, 2435, 654, 986, 345,  234, 3745,
      44,   33,   22,  77,   88,  99,  11,   22,  4,   5,    6,   8,
      3,    4,    6,   7443, 221, 4,   3475, 543, 769, 435,  145, 456,
      2463, 8789, 324, 1242, 34,  136, 678,  986, 44,  5463, 234, 789};

  auto before = system_clock::now();
  sort(input);
  auto after = system_clock::now();

  auto elapsed = duration_cast<microseconds>(after - before).count();
  cout << "elapsed time : " << elapsed << endl;

  for (auto& i : input) {
    cout << i << " ";
  }

  cout << endl;
  return 0;
}