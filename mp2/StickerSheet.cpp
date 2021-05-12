#include "StickerSheet.h"


StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  images_ = new Image*[max];
  x_coords_ = new unsigned[max];
  y_coords_ = new unsigned[max];
  max_ = max;
  size_ = 0;
  base_ = picture;
  width_ = picture.width();
  height_ = picture.height();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
  copy_(other);
}

StickerSheet::~StickerSheet() {
  destroy_();
}

void StickerSheet::destroy_() {
  if (images_ != NULL) {
    delete[] x_coords_;
    delete[] y_coords_;
    delete[] images_;
    images_ = NULL;
    x_coords_ = NULL;
    y_coords_ = NULL;
  }
}

void StickerSheet::copy_(const StickerSheet& other) {
  max_ = other.max_;
  width_ = other.width_;
  height_ = other.height_;
  size_ = other.size_;
  base_ = other.base_;
  images_ = new Image*[other.max_];
  x_coords_ = new unsigned[other.max_];
  y_coords_ = new unsigned[other.max_];
  for (unsigned i = 0; i < other.size_; i++) {
    images_[i] = other.images_[i];
    x_coords_[i] = other.x_coords_[i];
    y_coords_[i] = other.y_coords_[i];
  }
}

const StickerSheet& StickerSheet::operator=	(	const StickerSheet & 	other) {
  destroy_();
  copy_(other);
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  if (max < 1) {
    return;
  }
  if (max < size_) {
    size_ = max;
  }
  unsigned* tempx = new unsigned[max];
  unsigned* tempy = new unsigned[max];
  Image** temp = new Image*[max];
  for (unsigned i = 0; i < size_; i++) {
    temp[i] = images_[i];
    tempx[i] = x_coords_[i];
    tempy[i] = y_coords_[i];
  }
  delete[] images_;
  delete[] x_coords_;
  delete[] y_coords_;
  images_ = temp;
  y_coords_ = tempy;
  x_coords_ = tempx;
  tempx = NULL;
  tempy = NULL;
  temp = NULL;
  max_ = max;
}

int StickerSheet::addSticker(	Image & sticker, unsigned x, unsigned y) {
  if (size_ == max_) {
    return -1;
  }
  size_ += 1;
  images_[size_ - 1] = &sticker;
  x_coords_[size_ - 1] = x;
  y_coords_[size_ - 1] = y;
  return size_ - 1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index >= size_) {
    return false;
  }
  if (x > width_ || y > height_) {
    return false;
  }
  x_coords_[index] = x;
  y_coords_[index] = y;
  return true;
}


void StickerSheet::removeSticker(unsigned index) {
  if (index >= size_) {
    return;
  }
  else if (index == size_ - 1) {
    images_[index] = NULL;
    x_coords_[index] = 0;
    y_coords_[index] = 0;
  }
  else {
    for (unsigned i = index; i < size_; i++) {
      images_[i] = images_[i+1];
      x_coords_[i] = x_coords_[i+1];
      y_coords_[i] = y_coords_[i+1];
    }
  }
  size_ -=1;
}


Image* StickerSheet::getSticker(unsigned index) const {
  if (index >= size_) {
    return NULL;
  }
  return images_[index];
}

Image StickerSheet::render()const {
  Image sheet;
  sheet.resize(width_, height_);
  for (unsigned x = 0; x < width_; x++) {
    for (unsigned y = 0; y < height_; y++) {
      HSLAPixel & basePixel= base_.getPixel(x,y);
      HSLAPixel & sheetPixel = sheet.getPixel(x,y);
      if (basePixel.a != 0) {
        sheetPixel = basePixel;
      }
    }
  }



  for (unsigned i = 0; i < size_; i++) {
    Image layer = *images_[i];
    unsigned lower_x_bound = x_coords_[i];
    unsigned lower_y_bound = y_coords_[i];
    unsigned upper_x_bound;
    unsigned upper_y_bound;
    if (lower_x_bound + layer.width() - 1 > width_ - 1) {
      upper_x_bound = width_ - 1;
    }
    else {
      upper_x_bound = lower_x_bound + layer.width() - 1;
    }

    if (lower_y_bound + layer.height() - 1 > height_ - 1) {
      upper_y_bound = height_ - 1;
    }
    else {
      upper_y_bound = lower_y_bound + layer.height() - 1;
    }

    for (unsigned x = lower_x_bound; x <= upper_x_bound; x++) {
      for (unsigned y = lower_y_bound; y <= upper_y_bound; y++) {
        HSLAPixel & layerPixel= layer.getPixel(x - lower_x_bound, y - lower_y_bound);
        HSLAPixel & sheetPixel = sheet.getPixel(x,y);
        if (layerPixel.a != 0) {
          sheetPixel = layerPixel;
        }
      }
    }
  }
  return sheet;
  }

  int StickerSheet::get_size() {
    return size_;
  }
  int StickerSheet::get_max() {
    return max_;
  }
