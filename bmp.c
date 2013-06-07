//
//  bmp.c
//  lego-mosaic
//
//  Created by William Falk-Wallace on 1/2/13.
//  Copyright (c) 2013 William Falk-Wallace. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

static void die(const char *message)
{
    perror(message);
    exit(1);
}
//global bmp file 
FILE *bmpFile;
//global header
struct Header *h;
//global pixel array
struct pixelArray *p;

//open global bmp file
void openBMP(char *filepath)
{
	bmpFile = fopen (filepath, "rb");
    if (bmpFile == NULL)
        die("valid BMP file not found");
}

//closes global bmp
void closeBMP()
{
	//close the image
    fclose(bmpFile);
}

/*
 * Header needs to be stripped
 * FREE NOT YET IMPLEMENTED
 */
struct Header *getHeader()
{
    //malloc header struct
	h = (struct Header*) malloc(sizeof(struct Header));
    if(h == NULL)
        die("malloc failed");
	
	//populate header struct
	//why is it having trouble with the first two bits? something char related?
    fread(&(h->type), 2, 1, bmpFile);
    fread(&(h->filesize), 52, 1, bmpFile);
	//return header struct
    return h;
}

void printHeader()
{
    printf("\nBitmap Type:%s\n", h->type);
    printf("File Size:%d\n", h->filesize);
    printf("Reserve 1:%hd\n", h->reserve1);
    printf("Reserve 2:%hd\n", h->reserve2);
    printf("Offset:%d\n", h->offset);
    printf("Header Size:%d\n", h->header);
    printf("Width:%d\n", h->width);
    printf("Height:%d\n", h->height);
    printf("Color Planes Used:%hd\n", h->color_planes);
    printf("Bit Depth:%hd\n", h->bitdepth);
    printf("Compression:%d\n", h->compression);
    printf("Image Size:%d\n", h->imagesize);
    printf("X Resolution (px/m):%d\n", h->xres);
    printf("Y Resolution (px/m):%d\n", h->yres);
    printf("Palette Size:%d\n", h->palettesize);
    printf("Important Colors:%d\n\n", h->important_colors);
}

//get the pixel array; return POINTER TO RGB pixel array struct, int****
struct int ***getPixelArray()
{
	//skip the header
    fseek(bmpFile, h->offset - 1, SEEK_SET);

	//silly operator precedence
	//pointer to 
	int pixels[h->width][h->height][3];
	
	//malloc the array
    pixels = (int***) malloc(h->width * h->height * 3);
	if(pixels == NULL)
        die("malloc failed");
	
	//populate the array
	// i - width; j - height; k - R/G/B
    int i,j,k;
    for(i=0; i < h->width; i++)
    {
        for(j=0; j < h->height; j++)
        {
            for(k=0; k < 3; k++)
            {
                fread(pixelArray[i][j][2-k], 1, 1, bmpFile);
            }
        }
    }
	
	p->rgbArray = pixels;
	
    return p;
}

