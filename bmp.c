//
//  img.c
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

//header struct
struct BMPHeader
{
    unsigned char type[2];
    unsigned int filesize;
    unsigned short reserve1;
    unsigned short reserve2;
    unsigned int offset;
    unsigned int header;
    unsigned int width;
    unsigned int height;
    unsigned short color_planes;
    unsigned short bitdepth;
    unsigned int compression;
    unsigned int imagesize;
    unsigned int xres;
    unsigned int yres;
    unsigned int palettesize;
    unsigned int important_colors;
} header;

//img file path
FILE *imgFile;

//open img file
void imgOpen(char *filepath)
{
    if ((imgFile = fopen(filepath, "rb")) == NULL)
        die("valid file not found");
}

//close imgFile
void imgClose()
{
//close the image
    fclose(imgFile);
}

/*
* Header needs to be stripped
* TODO: FREE NOT YET IMPLEMENTED
*/
void populateHeader()
{
//populate header struct
//why is it having trouble with the first two bits? something char related.
    fread(&(header.type), 2, 1, imgFile);
    fread(&(header.filesize), 52, 1, imgFile);
    // fread(&(header.reserve1), 48, 1, imgFile);
}

void printHeader()
{
    printf("Bitmap Type:%s\n", header.type);
    printf("File Size:%d\n", header.filesize);
    printf("Reserve 1:%hd\n", header.reserve1);
    printf("Reserve 2:%hd\n", header.reserve2);
    printf("Offset:%d\n", header.offset);
    printf("Header Size:%d\n", header.header);
    printf("Width:%d\n", header.width);
    printf("Height:%d\n", header.height);
    printf("Color Planes Used:%hd\n", header.color_planes);
    printf("Bit Depth:%hd\n", header.bitdepth);
    printf("Compression:%d\n", header.compression);
    printf("Image Size:%d\n", header.imagesize);
    printf("X Resolution (px/m):%d\n", header.xres);
    printf("Y Resolution (px/m):%d\n", header.yres);
    printf("Palette Size:%d\n", header.palettesize);
    printf("Important Colors:%d\n", header.important_colors);
    
    printf("\nBitmap Type:%x %x\n", header.type[0], header.type[1]);
    printf("File Size:%x\n", header.filesize);
    printf("Reserve 1:%x\n", header.reserve1);
    printf("Reserve 2:%x\n", header.reserve2);
    printf("Offset:%x\n", header.offset);
    printf("Header Size:%x\n", header.header);
    printf("Width:%x\n", header.width);
    printf("Height:%x\n", header.height);
    printf("Color Planes Used:%x\n", header.color_planes);
    printf("Bit Depth:%x\n", header.bitdepth);
    printf("Compression:%x\n", header.compression);
    printf("Image Size:%x\n", header.imagesize);
    printf("X Resolution (px/m):%x\n", header.xres);
    printf("Y Resolution (px/m):%x\n", header.yres);
    printf("Palette Size:%x\n", header.palettesize);
    printf("Important Colors:%x\n", header.important_colors);
}

//get the pixel array
void populatePixelArray()
{
//skip the header
    fseek(imgFile, header.offset - 1, SEEK_SET);

    unsigned char pixels[header.width][header.height][3];

//populate the array
// i - width; j - height; k - R/G/B
    int i,j,k;
    for(i=0; i < header.width; i++)
    {
        for(j=0; j < header.height; j++)
        {
            for(k=0; k < 3; k++)
            {
                fread(&pixels[i][j][2-k], 1, 1, imgFile);
                // printf("%d,", pixels[i][j][2-k]);
            }
        }
    }

    // for(i=0; i < header.width; i++)
    // {
    //     for(j=0; j < header.height; j++)
    //     {
    //         for(k=0; k < 3; k++)
    //         {
    //             if(pixels[i][j][2-k] == 0)
    //                 pixels[i][j][2-k] += 10;
    //         }
    //     }
    // }

    FILE *output = fopen("updated.bmp","wb");
    fwrite(&header, 1, sizeof(header), output);
    for(j=0; j < header.height; j++){
        fprintf(output, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        fwrite(&pixels[i], sizeof(pixels[i]), 1, output);
        // fprintf(output, "\n");
    }
    
    fclose(output);
}

