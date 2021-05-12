/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet {

public:
  StickerSheet(const Image &picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet & other);
  const StickerSheet& operator=	(	const StickerSheet & 	other);
  void changeMaxStickers(unsigned max);
  int addSticker(	Image & sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image render()const;
  Image* getSticker(unsigned index) const;

  int get_size();
  int get_max();

private:
  Image base_;
  Image** images_;
  unsigned size_;
  unsigned max_;
  unsigned width_;
  unsigned height_;
  void destroy_();
  void copy_(const StickerSheet& other);
  unsigned* x_coords_;
  unsigned* y_coords_;




};
