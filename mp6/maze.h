/* Your code here! */
#pragma once

#include <vector>
#include "dsets.h"
#include "cs225/PNG.h"
#include <algorithm>
#include <time.h>
#include <queue>

using cs225::PNG;
using cs225::HSLAPixel;
using std::vector;
using std::pair;
using std::queue;

class SquareMaze {

private:
  DisjointSets cells_;
  vector<pair<bool,bool>> walls_;
  int width_;
  int height_;
  int solutionCell;

  int getX(int index) const;
  int getY(int index) const;
  int getIndex(int x, int y) const;
  bool canRemoveWall(int x, int y, int dir);

public:
  void printWalls();
  void printSet();
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  vector<int> solveMazeCustom(int start, int end);
  PNG* customDrawMazeWithSolution(int start, int end);
  PNG* drawMaze() const;
  PNG* drawMazeWithSolution();
  vector<int> scrambleIndexes(vector<int> indexes);





};
