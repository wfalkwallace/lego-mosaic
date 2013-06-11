//
//  bmp.h
//  lego-mosaic
//
//  Created by William Falk-Wallace on 1/3/13.
//  Copyright (c) 2013 William Falk-Wallace. All rights reserved.
//

#ifndef lego_mosaic_bmp_h
#define lego_mosaic_bmp_h

void imgOpen(char*);

void imgClose();

void populateHeader();

void printHeader();

void populatePixelArray();

#endif
