#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <cmath>
#include <iostream>

using namespace cs225;
using std::cout;
using std::endl;


MyColorPicker::MyColorPicker(HSLAPixel lineColor, HSLAPixel backgroundColor, int modifier, Point center)
: lineColor(lineColor), backgroundColor(backgroundColor), modifier(modifier), center(center) { }
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  //cout<< "x = " << x << ", ";
  //cout<< "center.x = " << center.x << ", ";
  double dx = (int)x - (int)center.x;
  //cout<< "dx = " << dx << ", ";
  double dy = (int)y - (int)center.y;
  //cout<< "dy = " << dy << ", ";
  double d = sqrt((dx * dx) + (dy * dy));
  //cout<< x << ", " << y << ": " << d;
  if ((int)d % modifier <= 2 ) {
    //cout<< ", is line" <<endl;
    return lineColor;
  }
  //cout<< ", is bg" <<endl;
  return backgroundColor;

}
