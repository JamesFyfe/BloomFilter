#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <stdio.h>
#include <jpeglib.h>

unsigned char* get_image_data(const char* input_filename);
void save_output_image(unsigned char *image_data, const char* output_filename, int width, int height, int num_components);
void apply_bloom(unsigned char *image_data, int width, int height, int num_components, float bloom_intensity, float threshold, int kernelSize);

#endif