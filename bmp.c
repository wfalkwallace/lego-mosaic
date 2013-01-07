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

/*
 * Header needs to be freed
 */
struct Header *getHeader(char *bmpPath)
{
    FILE *bmpFile = fopen (bmpPath, "rb");
    if (bmpFile == NULL)
        die("valid BMP file not found");
    struct Header *h = (struct Header*) malloc(sizeof(struct Header));
    if(h == NULL)
        die("malloc failed");
    fread(&(h->type), 2, 1, bmpFile);
    fread(&(h->filesize), 52, 1, bmpFile);
    fclose(bmpFile);
    return h;
}

void printHeader(struct Header *h)
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

//int ****getPixelArray(char *bmpPath)
//{
//    FILE *bmpFile = fopen(bmpPath, "rb");
//    if (bmpFile == NULL)
//        die("valid BMP file not found");
//    struct Header *h = getHeader(bmpPath);
//
//    fseek(bmpFile, h->offset - 1, SEEK_SET);
//    
//    int ****pixelArray = (int****) malloc(h->width * h->height * 3);
//    int i,j,k;
//    for(i=0; i < h->width; i++)
//    {
//        for(j=0; j < h->height; j++)
//        {
//            for(k=0; k < 3; k++)
//            {
//                fread(pixelArray[i][j][2-k], 1, 1, bmpFile);
//            }
//        }
//    }
//    
//    return pixelArray;
//}

