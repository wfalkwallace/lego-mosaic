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
    char bmpPath[] = "warning.bmp";
	openBMP(bmpPath);
	printf("Header:\n");
    getHeader();
    printHeader();
	printf("________________________\nHeader:\n");
	struct pixelArray *p = getPixelArray();
	printf("\n\ngot pixel array; size-%lu", sizeof(p));
	closeBMP();

    return 0;
}


