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
    char *bmpPath = "/Users/wgf2104/Desktop/IMG.bmp";
    struct Header *h = getHeader(bmpPath);
    printHeader(h);
    
    return 0;
}


