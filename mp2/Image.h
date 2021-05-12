/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
#pragma once

#include "cs225/PNG.h"
#include<utility>
using namespace cs225;
class Image: public PNG {

public:
  Image();
  int get_index();
  int get_x();
  int get_y();

  void set_index(int index);
  void set_x(int x);
  void set_y(int y);


  void lighten();
  void lighten(double amount);
  void darken();
  void darken(double amount);
  void saturate();
  void saturate(double amount);
  void desaturate();
  void desaturate(double amount);
  void grayscale();
  void rotateColor(double degrees);
  void illinify();
  void scale(double factor);
  void scale(unsigned w, unsigned h);

private:
  int index_;
  int x_;
  int y_;


};
