/* Your code here! */
#include "maze.h"
#include <iostream>

using std::cout;
using std::endl;

SquareMaze::SquareMaze() {
  height_ = 0;
  width_ = 0;
}

void SquareMaze::makeMaze(int width, int height){
  int numelem = width * height;
  width_ = width;
  height_ = height;

  //initialize all walls to have true,true pair for walls.
  for (int i = 0; i < numelem; i++) {
    walls_.push_back(pair<bool,bool>(true,true));
  }
  cells_.addelements(numelem);

  //initialize edges, pair-> first: index, second: 0 for right, 1 for down

  vector<pair<int,int>> edges;
  for (int i = 0; i < numelem; i++ ) {
    edges.push_back(pair<int,int>(i, 0));
    edges.push_back(pair<int,int>(i, 1));
  }
  srand(time(NULL));
  std::random_shuffle(std::begin(edges), std::end(edges));

  // for (size_t i = 0; i < edges.size(); i++) {
  //   cout<<"("<< edges[i].first << ", " << edges[i].second << "),";
  // }
  // cout<<endl;
  //
  // std::random_shuffle(std::begin(edges), std::end(edges));
  //
  // for (size_t i = 0; i < edges.size(); i++) {
  //   cout<<"("<< edges[i].first << ", " << edges[i].second << "),";
  // }
  // cout<<endl;

  for (size_t i = 0; i < edges.size(); i++) {
    int cur_idx = edges[i].first;
    int cur_dir = edges[i].second;
    bool s = canRemoveWall(getX(cur_idx), getY(cur_idx), cur_dir);

    //Test printing removed edges
    // if (s) {
    //   cout<< "Removed: ";
    //   cout<<"("<< edges[i].first << ", " << edges[i].second << "),";
    //   cout<<endl;
    // }

    if (cells_.size(0) == numelem) {
      break;
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  int cur_idx = getIndex(x,y);
  if (dir == 0) {
    return !walls_[cur_idx].first;
  }
  if (dir == 1) {
    return !walls_[cur_idx].second;
  }
  if (dir == 2 && (x-1) >= 0) {
    int left_idx = getIndex(x-1, y);
    return !walls_[left_idx].first;
  }
  if (dir == 3 && (y-1) >= 0) {
    int up_idx = getIndex(x, y-1);
    return !walls_[up_idx].second;
  }
return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  int cur_idx = getIndex(x,y);
  if (dir == 0) {
    walls_[cur_idx].first = exists;
  }
  if (dir == 1) {
    walls_[cur_idx].second = exists;
  }
  if (dir == 2 && (x-1) >= 0) {
    int left_idx = getIndex(x-1, y);
    walls_[left_idx].first  = exists;
  }
  if (dir == 3 && (y-1) >= 0) {
    int up_idx = getIndex(x, y-1);
    walls_[up_idx].second = exists;
  }
}

vector<int> SquareMaze::solveMaze() {
  vector<bool> visited;
  for (int i = 0; i < width_*height_; i++) {
    visited.push_back(false);
  }
  queue<int> q;
  q.push(0);
  vector<int> tree;
  tree.resize(width_*height_);
  tree[0] = -1;

  while (!q.empty()) {
    int a = q.front();
    int x = getX(a);
    int y = getY(a);
    q.pop();
    visited[a] = true;
    //add the proper adjacents
    if (canTravel(x, y, 0) && !visited[getIndex(x + 1, y)]) {
      q.push(getIndex(x+1, y));
      tree[getIndex(x+1, y)] = a;
    }
    if (canTravel(x, y, 1) && !visited[getIndex(x, y+1)]) {
      q.push(getIndex(x, y+1));
      tree[getIndex(x, y+1)] = a;
    }
    if (canTravel(x, y, 2) && !visited[getIndex(x - 1, y)]) {
      q.push(getIndex(x-1, y));
      tree[getIndex(x-1, y)] = a;
    }
    if (canTravel(x, y, 3) && !visited[getIndex(x, y-1)]) {
      q.push(getIndex(x, y-1));
      tree[getIndex(x, y-1)] = a;
    }
  }
  vector<int> solution;
  int biggest = 0;

  for (int x = 0; x < width_; x++) {
    int size = 0;
    int current = getIndex(x, height_ - 1);
    vector<int> curPath;
    while (current != -1) {
      curPath.push_back(current);
      size++;
      current = tree[current];
    }
    if (size > biggest) {
      biggest = size;
      solution = curPath;
    }
  }
  solutionCell = solution[0];
  std::reverse(solution.begin(), solution.end());
  vector<int> realsolution;
  for (size_t i = 1; i < solution.size(); i++) {
    int current = solution[i-1];
    if (getX(solution[i]) > getX(current) ) {
      realsolution.push_back(0);
    }
    else if (getX(solution[i]) < getX(current) ) {
      realsolution.push_back(2);
    }
    else if (getY(solution[i]) > getY(current) ) {
      realsolution.push_back(1);
    }
    else if (getY(solution[i]) < getY(current) ) {
      realsolution.push_back(3);
    }
  }
return realsolution;
}

PNG* SquareMaze::drawMaze() const {
  int imgwidth = width_*10 + 1;
  int imgheight =  height_*10 + 1;
  PNG* img = new PNG(imgwidth, imgheight);
  for (int x = 10; x < imgwidth; x++) {
    HSLAPixel& p = img->getPixel(x, 0);
    p.l = 0;
    p.s = 0;
  }
  for (int x = 0; x < imgwidth; x++) {
    HSLAPixel& p = img->getPixel(x, imgheight-1);
    p.l = 0;
    p.s = 0;
  }
  for (int y = 0; y < imgheight; y++) {
    HSLAPixel& p = img->getPixel(imgwidth-1, y);
    p.l = 0;
    p.s = 0;
  }
  for (int y = 0; y < imgheight; y++) {
    HSLAPixel& p = img->getPixel(0, y);
    p.l = 0;
    p.s = 0;
  }
  for (size_t i = 0; i < walls_.size(); i++) {
    int x = getX(i);
    int y = getY(i);
    if (walls_[i].first) {
      for (int k = 0; k <= 10; k++) {
        HSLAPixel& p = img->getPixel((x+1)*10,y*10+k);
        p.l = 0;
        p.s = 0;
      }
    }
    if (walls_[i].second) {
      for (int k = 0; k <= 10; k++) {
        HSLAPixel& p = img->getPixel(x*10+k, (y+1)*10);
        p.l = 0;
        p.s = 0;
      }
    }
  }


return img;
}

PNG* SquareMaze::drawMazeWithSolution() {
  PNG* solve = drawMaze();
  vector<int> soln = solveMaze();
  int currX = 5;
  int currY = 5;
  for(size_t i = 0; i < soln.size(); i++) {
    if (soln[i] == 0) {
      //cout<<"First Step: ";
      for (int k = 0; k<= 10; k++) {
        HSLAPixel& p = solve->getPixel(currX+k, currY);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      currX = currX + 10;
      //cout<<"Dir 0 New x: " << currX<<endl;
    }
    if (soln[i] == 1) {
      for (int k = 0; k<= 10; k++) {
        HSLAPixel& p = solve->getPixel(currX, currY+k);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      currY = currY + 10;
    //  cout<<"New y: " << currY<<endl;

    }
    if (soln[i] == 2) {
      for (int k = 0; k<= 10; k++) {
        HSLAPixel& p = solve->getPixel(currX-k, currY);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      currX = currX - 10;
      //cout<<"Dir 2 New x: " << currX<<endl;

    }
    if (soln[i] == 3) {
      for (int k = 0; k<= 10; k++) {
        HSLAPixel& p = solve->getPixel(currX, currY-k);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      currY = currY - 10;
      //cout<<"New y: " << currY<<endl;
    }
    int solnX = getX(solutionCell);
    int solnY = getY(solutionCell);
    for (int k = 1; k < 10; k++) {
      HSLAPixel& p = solve->getPixel(solnX*10+k, (solnY+1)*10);
      p.l = 1;
      p.s = 0;
    }

  }


return solve;
}

vector<int> SquareMaze::scrambleIndexes(vector<int> indexes) {
  // int size = indexes.size();
  // for (int i = 0; i < size; i++ ) {
  //   indexes.push_back(i);
  // }
  std::random_shuffle(std::begin(indexes), std::end(indexes));
  return indexes;
}

//dir = 0 for right, 1 for down
bool SquareMaze::canRemoveWall(int x, int y, int dir) {
  if (dir == 0 && (x+1) < width_) {
    if (cells_.find(getIndex(x,y)) != cells_.find(getIndex(x+1, y)) ) {
      cells_.setunion(getIndex(x,y), getIndex(x+1, y));
      walls_[getIndex(x,y)].first = false;

      return true;
    }
    else {
      return false;
    }
  }
  else if (dir == 1 && (y+1) < height_) {
    if (cells_.find(getIndex(x,y)) != cells_.find(getIndex(x, y+1)) ) {
      cells_.setunion(getIndex(x,y), getIndex(x, y+1));
      walls_[getIndex(x,y)].second = false;
      return true;
    }
    else {
      return false;
    }
  }
  return false;
}


int SquareMaze::getX(int index) const{
  return (index % width_);
}
int SquareMaze::getY(int index) const{
  return (index / width_);
}

int SquareMaze::getIndex(int x, int y) const{
  return (width_*y + x);
}

void SquareMaze::printWalls() {
  for (size_t i = 0; i < walls_.size(); i++) {
    cout<< i << ": R:" <<walls_[i].first << " B:" <<walls_[i].second <<endl;
  }
}
void SquareMaze::printSet() {
  cells_.print();
}


vector<int> SquareMaze::solveMazeCustom(int start, int end) {
  vector<bool> visited;
  for (int i = 0; i < width_*height_; i++) {
    visited.push_back(false);
  }
  queue<int> q;
  q.push(start);
  vector<int> tree;
  tree.resize(width_*height_);
  tree[start] = -1;

  while (!q.empty()) {
    int a = q.front();
    int x = getX(a);
    int y = getY(a);
    q.pop();
    visited[a] = true;
    //add the proper adjacents
    if (canTravel(x, y, 0) && !visited[getIndex(x + 1, y)]) {
      q.push(getIndex(x+1, y));
      tree[getIndex(x+1, y)] = a;
    }
    if (canTravel(x, y, 1) && !visited[getIndex(x, y+1)]) {
      q.push(getIndex(x, y+1));
      tree[getIndex(x, y+1)] = a;
    }
    if (canTravel(x, y, 2) && !visited[getIndex(x - 1, y)]) {
      q.push(getIndex(x-1, y));
      tree[getIndex(x-1, y)] = a;
    }
    if (canTravel(x, y, 3) && !visited[getIndex(x, y-1)]) {
      q.push(getIndex(x, y-1));
      tree[getIndex(x, y-1)] = a;
    }
  }
  int current = getIndex(end, height_ - 1);
  vector<int> solution;
  while (current != -1) {
    solution.push_back(current);
    current = tree[current];
  }

  solutionCell = solution[0];
  std::reverse(solution.begin(), solution.end());
  vector<int> realsolution;
  for (size_t i = 1; i < solution.size(); i++) {
    int current = solution[i-1];
    if (getX(solution[i]) > getX(current) ) {
      realsolution.push_back(0);
    }
    else if (getX(solution[i]) < getX(current) ) {
      realsolution.push_back(2);
    }
    else if (getY(solution[i]) > getY(current) ) {
      realsolution.push_back(1);
    }
    else if (getY(solution[i]) < getY(current) ) {
      realsolution.push_back(3);
    }
  }
return realsolution;
}

PNG* SquareMaze::customDrawMazeWithSolution(int start, int end) {
  PNG* solve = drawMaze();
  vector<int> soln = solveMazeCustom(start, end);
  int currX = 5 + 10*start;
  int currY = 5;
  for(size_t i = 0; i < soln.size(); i++) {
    if (soln[i] == 0) {
      //cout<<"First Step: ";
      for (int k = 0; k<= 10; k++) {
        HSLAPixel& p = solve->getPixel(currX+k, currY);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      currX = currX + 10;
      //cout<<"Dir 0 New x: " << currX<<endl;
    }
    if (soln[i] == 1) {
      for (int k = 0; k<= 10; k++) {
        HSLAPixel& p = solve->getPixel(currX, currY+k);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      currY = currY + 10;
    //  cout<<"New y: " << currY<<endl;

    }
    if (soln[i] == 2) {
      for (int k = 0; k<= 10; k++) {
        HSLAPixel& p = solve->getPixel(currX-k, currY);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      currX = currX - 10;
      //cout<<"Dir 2 New x: " << currX<<endl;

    }
    if (soln[i] == 3) {
      for (int k = 0; k<= 10; k++) {
        HSLAPixel& p = solve->getPixel(currX, currY-k);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      currY = currY - 10;
      //cout<<"New y: " << currY<<endl;
    }
    int startX = getX(start);
    int startY = getY(start);
    int solnX = getX(solutionCell);
    int solnY = getY(solutionCell);
    for (int k = 1; k < 10; k++) {
      HSLAPixel& p = solve->getPixel(solnX*10+k, (solnY+1)*10);
      p.l = 1;
      p.s = 0;
    }
    for (int x = 0; x < 20; x++) {
      HSLAPixel& p = solve->getPixel(x, 0);
      p.l = 0;
      p.s = 0;
    }
    for (int k = 1; k < 10; k++) {
      HSLAPixel& p = solve->getPixel(startX*10+k, 0);
      p.l = 1;
      p.s = 0;
    }

  }


return solve;
}
