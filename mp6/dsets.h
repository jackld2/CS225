/* Your code here! */
#pragma once

#include <vector>

using std::vector;

class DisjointSets {

private:
  vector<int> arr_;

public:
  void addelements(int num);
  int find(int elem);
  void setunion(int a, int b);
  int size(int elem);
  void print();

};
