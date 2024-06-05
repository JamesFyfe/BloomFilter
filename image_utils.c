#include "image_utils.h"
#include <stdlib.h>

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
    int num_color_components = cinfo.num_components;

    // Allocate memory for pixel data
    unsigned char *image_data = malloc(width * height * num_color_components);

    // Read pixel data into buffer
    while (cinfo.output_scanline < cinfo.output_height) {
        unsigned char *buffer_array[1];
        buffer_array[0] = image_data + (cinfo.output_scanline) * width * num_color_components;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    return image_data;
}