/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <iostream>
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{

  int rows = theSource.getRows();
  int columns = theSource.getColumns();

  map<Point<3>, int> tileLibrary;
  vector<Point<3>> tilePoints;

  for (size_t i = 0; i < theTiles.size(); i++) {
    tileLibrary.insert(pair<Point<3>, int>(
      convertToXYZ(theTiles[i].getAverageColor()), i ));
      tilePoints.push_back(convertToXYZ(theTiles[i].getAverageColor()));
  }

  KDTree<3> imgTree(tilePoints);

  MosaicCanvas* result = new MosaicCanvas(rows, columns);

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      Point<3> currSrcPoint = convertToXYZ(theSource.getRegionColor(r,c));
      //cout<< "Source Point: " << currSrcPoint<<endl;
      Point<3> nearest = imgTree.findNearestNeighbor(currSrcPoint);
      //TileImage bestFit = theTiles[tileLibrary[nearest]];

      //TileImage* copy = new TileImage(bestFit);
      result->setTile(r, c, &theTiles[tileLibrary[nearest]]);
      //cout<<"("<<r<<","<<c<<")"<<endl;
    }
  }
  //cout<<"FINISHED"<<endl;
  //cout<<"Mosaic:"<< endl;

  // for (int r = 0; r < rows; r++) {
  //   for (int c = 0; c < columns; c++) {
  //     cout<< convertToXYZ(result->getTile(r,c).getAverageColor())<< endl;
  //   }
  // }
  //cout<<"SECOND FINISH"<<endl;

    /**
     * @todo Implement this function!
     */

    return result;
}
