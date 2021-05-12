/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

     if (first[curDim] < second[curDim]) {
       return true;
     }
     else if (first[curDim] > second[curDim]) {
       return false;
     }
     else {
       return first < second;
     }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double pot_dist = 0;
     double curr_dist = 0;

     for (int i = 0; i < Dim; i++) {
       pot_dist += ( (target[i] - potential[i]) * (target[i] - potential[i]) );
       curr_dist += ( (target[i] - currentBest[i]) * (target[i] - currentBest[i]) );
     }

     if (pot_dist < curr_dist) {
       return true;
     }
     else if (curr_dist < pot_dist) {
       return false;
     }
     else {
       return potential < currentBest;
     }
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, int left, int right, int pivotIndex, int dim) {

  Point<Dim> pivotValue = points[pivotIndex];
  Point<Dim> temp = points[pivotIndex];
  points[pivotIndex] = points[right];
  points[right] = temp;

  int storeIndex = left;

  for (int i = left; i <= right - 1; i ++) {
    if (smallerDimVal(points[i], pivotValue, dim)) {
      //cout<< points[i] << " is less than " << pivotValue<< endl;
      Point<Dim> temp2 = points[storeIndex];
      points[storeIndex] = points[i];
      points[i] = temp2;
      storeIndex++;
    }
  }

  Point<Dim> temp3 = points[right];
  points[right] = points[storeIndex];
  points[storeIndex] = temp3;
  return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& points, int left, int right, int k, int dim) {
  if (left == right) {
    return points[left];
  }
  int pivotIndex = ((right + left) / 2);
  pivotIndex = partition(points, left, right, pivotIndex, dim);
  if (k == pivotIndex) {
    return points[k];
  }
  else if (k < pivotIndex) {
    return select(points, left, pivotIndex - 1, k, dim);
  }
  else {
    return select(points, pivotIndex + 1, right, k, dim);
  }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::construct(vector<Point<Dim>>& points, int left, int right, int dim) {
  // if (right == left) {
  //   cout<<"REACHED ENDNODE:" << points[left]<<endl;
  //   KDTreeNode* endNode = new KDTreeNode(points[left]);
  //   endNode->left = NULL;
  //   endNode->right = NULL;
  //   return endNode;
  // }
  if (left > right || right < left) {
    //cout<<"NULL:"<<endl;
    return NULL;
  }
  int k;
  if ((right - left)%2 == 0) {
    k = (left + right) / 2;
  }
  else {
    k = ((left + right) - 1) / 2;
  }
  Point<Dim> mid = select(points, left, right, k, dim);
  KDTreeNode* node = new KDTreeNode(mid);
  //cout<<"ADDED: " << mid <<endl;
  //return nod
  node->left = construct(points, left, k-1, ((dim + 1) % Dim) );
  node->right = construct(points, k+1 ,right, ((dim + 1) % Dim) );

  // node->left = construct(points, left, k-1, ((dim + 1) % Dim) );
  // node->right = construct(points, k+1 ,right, ((dim + 1) % Dim) );
  return node;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     size = newPoints.size();
     //deep copy of newPoints
     vector<Point<Dim>> copyVec;
     for (size_t i = 0; i < newPoints.size(); i++) {
       copyVec.push_back(newPoints[i]);
     }
     root = construct(copyVec, 0, copyVec.size() - 1, 0);

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const typename KDTree<Dim>::KDTreeNode* original) {
  if (original == NULL) {
    return NULL;
  }
  KDTreeNode* copyNode = new KDTreeNode(original->point);
  copyNode->left = copy(original->left);
  copyNode->right = copy(original->right);
  return copyNode;

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   root = copy(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   destroy(root);
   root = copy(rhs.root);

  return *this;
}

template <int Dim>
void KDTree<Dim>::destroy(typename KDTree<Dim>::KDTreeNode* node) {
  if (node != NULL) {
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = NULL;
  }
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   destroy(root);
   root = NULL;
}

// template <int Dim>
// Point<Dim> KDTree<Dim>::nearestNode(const Point<Dim>& query, Point<Dim> currentBest,
//   typename KDTree<Dim>::KDTreeNode* node, int dim  ) const {
//
//     cout<<"RECURSION AFTERWARD:"<< endl;
//     cout<<node->point<<endl;
//     //cout<<node->left->point<< ", " << node->right->point<<endl;
//     if (node->point == query) {
//       currentBest = node->point;
//       cout<<"Found exact: " << currentBest<<endl;
//     }
//     else if (!smallerDimVal(node->point, query, dim) && node->left != NULL) {
//       cout<<"WENT LEFT: Current Node: "<< node->point << " greater than Query: "<< query <<endl;
//       return nearest(query, currentBest, node->left, ((dim + 1) % Dim) );
//       cout<<"RECURSION?"<<endl;
//     }
//     else if (smallerDimVal(node->point, query, dim) && node->right != NULL) {
//       cout<<"WENT RIGHT: Current Node: "<< node->point << " less than Query: "<< query <<endl;
//       return nearest(query, currentBest, node->right, ((dim + 1) % Dim) );
//       cout<<"RECURSION?"<<endl;
//     }
//     else {
//       currentBest = node->point;
//       cout<<"End reached: " << currentBest<<endl;
//     }
//
//     cout<<"RECURSION BEFORE RETURN? "<< node->point <<endl;
//     if (shouldReplace(query, currentBest, node->point)) {
//       cout<<"REPLACEMENT:";
//       currentBest = node->point;
//     }
//     return currentBest;
// }


template <int Dim>
void KDTree<Dim>::nearestNode(Point<Dim>& query, Point<Dim>& currentBest,
  typename KDTree<Dim>::KDTreeNode* node, int dim  ) const {

    if (smallerDimVal(query, node->point, dim)) {
      if (node->left == NULL) {
        if( shouldReplace (query, currentBest, node->point)) {
          currentBest = node->point;
        }
        return;
      }
      nearestNode(query, currentBest, node->left, (dim + 1) % Dim );
      if (shouldReplace(query, currentBest, node->point)) {
        currentBest = node->point;
      }
      if (pow(abs(query[dim] - node->point[dim]),2) <= pointDistance(query, currentBest)) { //PROBLEM IS HERE
        if (node->right != NULL)
          nearestNode(query, currentBest, node->right, (dim + 1) % Dim );
        }
      }
      else {
    if (node->right == NULL) {
      if (shouldReplace(query, currentBest, node->point)){
        currentBest = node->point;
      }
      return;
  }
    nearestNode(query, currentBest, node->right, (dim + 1) % Dim );

        if (shouldReplace(query, currentBest, node->point)) {
          currentBest = node->point;
        }
        if (pow(abs(query[dim] - node->point[dim]),2) <= pointDistance(query, currentBest)) {
          if (node->left != NULL)
          nearestNode(query, currentBest, node->left, (dim + 1) % Dim );
        }
}
}


template <int Dim>
double KDTree<Dim>::pointDistance(Point<Dim>& a, Point<Dim>& b) const {
  double difference = 0;
  for (int i = 0; i < Dim; i++) {
    difference += ((a[i] - b[i]) * (a[i] - b[i]));
  }
  return difference;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{

    /**
     * @todo Implement this function!
     */
    Point<Dim> target = query;
    double pointValues[Dim];
    for (int i = 0; i < Dim; i++) {
      pointValues[i] = 100000;
    }

    Point<Dim> currentBest(pointValues);
    nearestNode(target, currentBest, root, 0);
    return currentBest;
}
