/* Your code here! */
#include "dsets.h"
#include <iostream>
using std::cout;
using std::endl;

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    arr_.push_back(-1);
  }

}

int DisjointSets::find(int elem) {
  if (arr_[elem] < 0) {
    return elem;
  }
  else {
    int root = find(arr_[elem]);
    arr_[elem] = root;
    return root;
  }
}
void DisjointSets::setunion(int a, int b) {

 int root1 = find(a);
 int root2 = find(b);

 if (root1 == root2) {
  return;
}
 int newSize = arr_[root1] + arr_[root2];
  if (arr_[root1] <= arr_[root2]) {
    arr_[root2] = root1;
    arr_[root1] = newSize;
  }
  else {
    arr_[root1] = root2;
    arr_[root2] = newSize;
  }
}
int DisjointSets::size(int elem) {
  return -1 * arr_[find(elem)];
}

void DisjointSets::print() {

  for (size_t i = 0; i < arr_.size(); i++) {
    cout<<"["<<arr_[i]<<"] ";
  }
  cout<<endl;
}
