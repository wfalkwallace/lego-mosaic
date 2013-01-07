//
//  bmp.h
//  lego-mosaic
//
//  Created by William Falk-Wallace on 1/3/13.
//  Copyright (c) 2013 William Falk-Wallace. All rights reserved.
//

#ifndef lego_mosaic_bmp_h
#define lego_mosaic_bmp_h

struct Header
{
    char type[2];
    int filesize;
    short reserve1;
    short reserve2;
    int offset;
    int header;
    int width;
    int height;
    short color_planes;
    short bitdepth;
    int compression;
    int imagesize;
    int xres;
    int yres;
    int palettesize;
    int important_colors;
};

struct Header *getHeader(char*);

void printHeader(struct Header*);

int ****getPixelArray(char*);

#endif
