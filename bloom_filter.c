#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_image> <output_image> <bloom_intensity>\n", argv[0]);
        return 1;
    }

    char *input_image = argv[1];
    char *output_image = argv[2];
    float bloom_intensity = atof(argv[3]);

    // TODO: Implement the following steps:
    // 1. Read the input image
    // 2. Apply the bloom filter
    // 3. Save the output image

    printf("Input image: %s\n", input_image);
    printf("Output image: %s\n", output_image);
    printf("Bloom intensity: %.2f\n", bloom_intensity);

    return 0;
}