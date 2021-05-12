#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
using cs225::PNG;
using cs225::HSLAPixel;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze maze1;
    SquareMaze maze2;
    SquareMaze maze3;
    SquareMaze maze4;
  	maze1.makeMaze(5,5);
    maze2.makeMaze(7,7);
    maze3.makeMaze(9,9);
    maze4.makeMaze(11,11);
    maze1.solveMazeCustom(2,2);
    maze2.solveMazeCustom(2,3);
    maze3.solveMazeCustom(3,4);
    maze4.solveMazeCustom(4,5);
    PNG* mazeimg1 = maze1.customDrawMazeWithSolution(2,2);
    PNG* mazeimg2 = maze2.customDrawMazeWithSolution(2,3);
    PNG* mazeimg3 = maze3.customDrawMazeWithSolution(3,4);
    PNG* mazeimg4 = maze4.customDrawMazeWithSolution(4,5);
    int width = mazeimg4->width();
    int height = mazeimg1->height() + mazeimg2->height() + mazeimg3->height() + mazeimg4->height();
    PNG* final = new PNG(width, height);
    size_t yoffset = 0;

    for (size_t x = 0; x < mazeimg1->width(); x++) {
      for (size_t y = 0; y < mazeimg1->height(); y++) {
        HSLAPixel& p = final->getPixel(x, y);
        p = mazeimg1->getPixel(x,y);
      }
    }
    yoffset += mazeimg1->height()-1;
    for (size_t x = 0; x < mazeimg2->width(); x++) {
      for (size_t y = 0; y < mazeimg2->height(); y++) {
        HSLAPixel& p = final->getPixel(x, y + yoffset );
        p = mazeimg2->getPixel(x,y);
      }
    }
    yoffset += mazeimg2->height()-1;
    for (size_t x = 0; x < mazeimg3->width(); x++) {
      for (size_t y = 0; y < mazeimg3->height(); y++) {
        HSLAPixel& p = final->getPixel(x, y + yoffset);
        p = mazeimg3->getPixel(x,y);
      }
    }
    yoffset += mazeimg3->height()-1;
    for (size_t x = 0; x < mazeimg4->width(); x++) {
      for (size_t y = 0; y < mazeimg4->height(); y++) {
        HSLAPixel& p = final->getPixel(x, y + yoffset);
        p = mazeimg4->getPixel(x,y);
      }
    }

  	//maze.printSet();
  	//maze.printWalls();
    cout<<"Made maze"<<endl;
    final->writeToFile("creative.png");
    return 0;
}
