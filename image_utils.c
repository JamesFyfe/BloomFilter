#include "image_utils.h"
#include <stdlib.h>
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

unsigned char* get_image_data(const char* input_filename) {
    FILE *infile = fopen(input_filename, "rb");
    if (!infile) {
        fprintf(stderr, "Error opening input file\n");
        return NULL;
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // Setup decompression
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int num_components = cinfo.num_components;

    // Allocate memory for pixel data
    unsigned char *image_data = malloc(width * height * num_components);

    // Read pixel data into buffer
    while (cinfo.output_scanline < cinfo.output_height) {
        unsigned char *buffer_array[1];
        buffer_array[0] = image_data + (cinfo.output_scanline) * width * num_components;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    return image_data;
}

void save_output_image(unsigned char *image_data, const char* output_filename, int width, int height, int num_components) {
    FILE *outfile = fopen(output_filename, "wb");
    if (!outfile) {
        fprintf(stderr, "Error opening output file\n");
        return;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // setup compression
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = num_components;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    int compression_quality = 90;
    jpeg_set_quality(&cinfo, compression_quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height) {
        unsigned char *buffer_array[1];
        buffer_array[0] = image_data + (cinfo.next_scanline) * width * num_components;
        jpeg_write_scanlines(&cinfo, buffer_array, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);
}

void apply_bloom(unsigned char *image_data, int width, int height, int num_components, float bloom_intensity, float threshold, int kernelSize) {

    // calculate bloom_data
    unsigned char *bloom_data = calloc(1, width * height * num_components);
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            int index = (h * width + w) * num_components;
            unsigned char r = image_data[index];
            unsigned char g = image_data[index + 1];
            unsigned char b = image_data[index + 2];
            
            float avg = (r + g + b) / 765.0;
            
            if (avg > threshold) {
                for(int kh = -kernelSize; kh < kernelSize; kh++) {
                    for(int kw = -kernelSize; kw < kernelSize; kw++) {
                        int pixelLocation = ((h + kh) * width + w + kw) * num_components;
                        if(pixelLocation > height * width * num_components) {
                            // pixel is outside of image
                            continue;
                        }
                        float distance = sqrt(kw * kw + kh * kh);
                        if(distance > kernelSize) {
                            // to make blur circular instead of square
                            continue;
                        }
                        float bloomStrengthAtPixel = bloom_intensity / distance;
                        bloom_data[pixelLocation] = MIN(bloom_data[pixelLocation] + r * bloomStrengthAtPixel, 255);
                        bloom_data[pixelLocation + 1] = MIN(bloom_data[pixelLocation + 1] + g * bloomStrengthAtPixel, 255);
                        bloom_data[pixelLocation + 2] = MIN(bloom_data[pixelLocation + 2] + b * bloomStrengthAtPixel, 255);
                    }
                }
            }
        }
    }

    // add bloom_data to image_data
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            int index = (h * width + w) * num_components;
            image_data[index] = MIN(image_data[index] + bloom_data[index], 255);
            image_data[index + 1] = MIN(image_data[index + 1] + bloom_data[index + 1], 255);
            image_data[index + 2] = MIN(image_data[index + 2] + bloom_data[index + 2], 255);
        }
    }

    free(bloom_data);
    
    return;
}
