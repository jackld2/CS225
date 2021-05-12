
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;
  png.readFromFile("white.png");

  FloodFilledImage image(png);
  BFS bfs(png, Point(100, 100), 0.2);

  HSLAPixel color(0, 0, 0);
  HSLAPixel color2(0, 1, 1);
  MyColorPicker pattern1(color, color2, 20, Point(100, 100));
  MyColorPicker pattern2(color, color2, 4, Point(100, 100));
  image.addFloodFill(bfs, pattern1 );

  DFS dfs1(png, Point(110, 100), 0.2);
  image.addFloodFill(dfs1, pattern2 );

  Animation animation = image.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
