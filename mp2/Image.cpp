#include "Image.h"
#include <iostream>
#include <cmath>
#include <vector>


Image::Image() {
  index_ = 0;
  x_ = 0;
  y_ = 0;
}

int Image::get_index() {
  return index_;
}

int Image::get_x() {
  return x_;
}

int Image::get_y() {
  return y_;
}

void Image::set_index(int index) {
  index_ = index;
}
void Image::set_x(int x) {
  x_ = x;
}
void Image::set_y(int y) {
  y_ = y;
}


void Image::lighten() {
  lighten(0.1);
}

void Image::lighten(double amount) {
  for (unsigned x = 0; x < width(); x++ ) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.l + amount <= 1) {
        pixel.l += amount;
      }
      else {
        pixel.l = 1;
      }
    }
  }
}

void Image::darken(){
  darken(0.1);
}
void Image::darken(double amount){
  for (unsigned x = 0; x < width(); x++ ) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.l - amount >= 0) {
        pixel.l -= amount;
      }
      else {
        pixel.l = 0;
      }
    }
  }
}

void Image::saturate(){
  saturate(0.1);
}

void Image::saturate(double amount){
  for (unsigned x = 0; x < width(); x++ ) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.s + amount <= 1) {
        pixel.s += amount;
      }
      else {
        pixel.s = 1;
      }
    }
  }
}

void Image::desaturate(){
desaturate(0.1);
}

void Image::desaturate(double amount){
  for (unsigned x = 0; x < width(); x++ ) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.s - amount >= 0) {
        pixel.s -= amount;
      }
      else {
        pixel.s = 0;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned x = 0; x < width(); x++ ) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x,y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < width(); x++ ) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x,y);
      if (pixel.h + degrees > 360) {
        pixel.h = pixel.h + degrees - 360;
      }
      else if ( pixel.h + degrees < 0) {
        pixel.h = pixel.h + degrees + 360;
      }
      else {
        pixel.h = pixel.h + degrees;
      }
    }
  }
}

void Image::illinify(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if ( (std::abs(pixel.h - 216) > std::abs(pixel.h - 11)) ) {
        pixel.h = 11;
      }
      else if ((std::abs(pixel.h - 216) > std::abs(pixel.h - 371))) {
        pixel.h = 11;
      }
      else {
        pixel.h = 216;
      }
    }
  }
}

void Image::scale(double factor){
  scale(round(factor * this->width()), round(factor * this->height()));

}
void Image::scale(unsigned w, unsigned h){
  double height = (double)this->height();
  double width = (double)this->width();

  Image scaled;
  scaled.resize(w, h);

  double x_ratio = width/ (double)w;
  double y_ratio = height / (double)h;
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {

      int newX = floor(x_ratio * x);
      int newY = floor(y_ratio * y);
      HSLAPixel & origPixel = getPixel(newX,newY);
      HSLAPixel & newPixel = scaled.getPixel(x,y);
      newPixel = origPixel;
    }
  }
  *this = scaled;
}
