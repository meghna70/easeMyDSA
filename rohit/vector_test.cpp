#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

#include "vector.h"

void print(vector<int> &arr) {
  for (auto x : arr) {
    cout << x << " ";
  }
  cout << "\n";
}

void print(vec &arr) {
  for (int i = 0; i < arr.len; i++) {
    cout << arr.data[i] << " ";
  }
  cout << "\n";
}

int main() {
  // Unfortunately this is needed for quicksort to work effectively
  srand(time(nullptr));

  vec customVector;
  vec_init(&customVector);

  // vector<int> stdVector;

  for (int i = 0; i < 50'000; i++) {
    int random = rand() % 100;
    vec_push(&customVector, random);
    // stdVector.push_back(random);
  }

  vec_sort(&customVector);
  // sort(stdVector.begin(), stdVector.end());

  //   print(customVector);
  //   print(stdVector);
}
