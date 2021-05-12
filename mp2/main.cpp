#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image thanos; thanos.readFromFile("customPics/thanos.png");
  thanos.scale(1.5);
  Image major; major.readFromFile("customPics/major.png");
  major.scale(0.5);
  Image grave; grave.readFromFile("customPics/grave.png");
  Image yes; yes.readFromFile("customPics/yes.png");
  yes.scale(0.5);
  Image cost; cost.readFromFile("customPics/cost.png");
  cost.scale(0.5);
  Image everything; everything.readFromFile("customPics/everything.png");
  everything.scale(0.5);



  StickerSheet sheet(thanos, 6);
  sheet.addSticker(major, 5, 300);
  sheet.addSticker(grave, 1536-435,1035-297);
  sheet.addSticker(yes, 1536*0.75 - 20, 400 );
  sheet.addSticker(cost, 100, 900);
  sheet.addSticker(everything, 1536/2 + 20, 550);

  Image out;
  out = sheet.render();
  out.writeToFile("myImage.png");

  return 0;
}
