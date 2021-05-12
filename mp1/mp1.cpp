#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;
using std::pair;

#include <string>
#include <cmath>


pair <int,int> drawVector(PNG &image, int x, int y, int length, double angle, int color);
void drawTree(PNG &image, int x, int y, int length, double angle, int color);

void rotate(std::string inputFile, std::string outputFile) {
  PNG image = PNG();
  image.readFromFile(inputFile);

  //swap pixels of each half of the images (seperated top and bottom)
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < floor(image.height()/2); y++) {
      HSLAPixel & pixelTop = image.getPixel(x, y);
      HSLAPixel & pixelBottom = image.getPixel((image.width()-1) - x, (image.height()-1)- y);
      HSLAPixel pixelTemp = pixelTop;
      pixelTop = pixelBottom;
      pixelBottom = pixelTemp;
    }
  }
  //If the image has an odd amount of vertical pixels,swap middle roll by seprating row on half and swapping
  if (image.height()%2 != 0) {
    for (unsigned x = 0; x < ceil(image.width()/2); x++) {
      HSLAPixel & pixelTop = image.getPixel(x, floor(image.height()/2));
      HSLAPixel & pixelBottom = image.getPixel((image.width()-1) - x, floor(image.height()/2));
      HSLAPixel pixelTemp = pixelTop;
      pixelTop = pixelBottom;
      pixelBottom = pixelTemp;
    }
  }
  image.writeToFile(outputFile);
}

 std::pair<int,int> drawVector(PNG &image, int x, int y, int length, double angle, int color) {
   for (unsigned i = 0; i < length; i++) {
     int pixelX = round(i*sin(angle) + x);
     int pixelY = round(i*cos(angle) + y);
     HSLAPixel & pixel = image.getPixel(pixelX, pixelY);
     pixel = HSLAPixel(color, 0.5, 0.5);
   }
   int finalX = round(length*sin(angle) + x);
   int finalY = round(length*cos(angle) + y);
   return std::pair<int,int>(finalX,finalY);
}
void drawTree(PNG &image, int x, int y, int length, double angle, int color) {
  std::pair<int, int> coord = drawVector(image, x, y, length, angle, color);
  if (length > 8 && (x < image.width() - 1 && y < image.height() - 1)) {

    drawTree(image, coord.first, coord.second, length * 0.8, angle + 0.2, (color + 20)%360);
    drawTree(image, coord.first, coord.second, length * 0.8, angle - 0.2, (color + 20)%360);
  }
}
PNG myArt(unsigned int width, unsigned int height) {
  PNG image = PNG(width, height);
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);
      pixel.l = 0;
    }
  }
  drawTree(image, 400, 0, 160, 0.0, 180);





  return image;
}
