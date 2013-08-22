//
//  main.c
//  lego-mosaic
//
//  Created by William Falk-Wallace on 1/2/13.
//  Copyright (c) 2013 William Falk-Wallace. All rights reserved.
//

#include <stdio.h>
#include "bmp.h"


int main(int argc, const char * argv[])
{
    char bmpPath[] = "sample.bmp";
	imgOpen(bmpPath);
	// printf("\nHeader:\n");
    populateHeader();
    // printHeader();
	// printf("________________________\n\nPixel Array:\n");
	populatePixelArray();
	printf("got pixel array!\n");
	imgClose();
    return 0;
}


