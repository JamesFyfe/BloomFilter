#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <stdio.h>
#include <jpeglib.h>

unsigned char* get_image_data(const char* input_filename);

#endif