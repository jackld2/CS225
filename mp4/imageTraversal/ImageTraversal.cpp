#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include <iostream>
using std::cout;
using std::endl;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal& traversal, int height, int width, double tolerance, Point start, PNG image) {
  traversal_ = &traversal;
  height_ = height;
  width_ = width;
  tol_ = tolerance;
  start_ = start;
  image_ = image;
  current_ = start;

  visited_.resize(height_);
  for(int i = 0; i < height; i++) {
    visited_[i].resize(width_, false);
  }
  //++*this;
}
ImageTraversal::Iterator::~Iterator() {
  delete traversal_;
}

ImageTraversal::~ImageTraversal() {}


double ImageTraversal::Iterator::getDelta(Point a, Point b) {
  return calculateDelta(image_.getPixel(a.x,a.y), image_.getPixel(b.x,b.y));
}

bool ImageTraversal::Iterator::canAdd(Point p) {
  if (p.x >= width_ || p.y >= height_) return false;
  if (getDelta(start_, p) >= tol_) return false;
  if (wasVisited(p)) return false;
  return true;
}

bool ImageTraversal::Iterator::wasVisited(Point p) {
  return visited_[p.y][p.x];
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  if (!traversal_->empty()) {
    current_ = traversal_->pop();
    //cout<< "CURRENT: " << current_ <<endl;
    visited_[current_.y][current_.x] = true;

    //add 4 points with conditions
    if (canAdd(Point(current_.x + 1,current_.y))) {
      traversal_->add(Point(current_.x + 1,current_.y));
    }
    if (canAdd(Point(current_.x,current_.y + 1))) {
      traversal_->add(Point(current_.x,current_.y + 1));
    }
    if (canAdd(Point(current_.x - 1,current_.y))) {
      traversal_->add(Point(current_.x - 1,current_.y));
    }
    if (canAdd(Point(current_.x, current_.y - 1))) {
      traversal_->add(Point(current_.x, current_.y - 1));
    }

    while (wasVisited(traversal_->peek()) && !traversal_->empty()) {
      //cout<< "Extra pop peek: " << traversal_->peek()<<endl;
      traversal_->pop();
      //cout<< "Extra pop"<<endl;
    }
  }
  current_ = traversal_->peek();
  //cout<< endl;
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //cout<<"Dereference"<<endl;
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;
  if (traversal_ == NULL) { thisEmpty = true;}
  if (other.traversal_ == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = traversal_->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal_->empty(); }

  if (thisEmpty && otherEmpty) return false;
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal_ != other.traversal_);
  else return true;
}
