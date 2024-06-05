#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_image> <output_image> <bloom_intensity>\n", argv[0]);
        return 1;
    }

    char *input_image = argv[1];
    char *output_image = argv[2];
    float bloom_intensity = atof(argv[3]);

		printf("Input image: %s\n", input_image);
    printf("Output image: %s\n", output_image);
    printf("Bloom intensity: %.2f\n", bloom_intensity);
		// TODO add kernel size and brightness threshold

    // read input image into data
		unsigned char *image_data = get_image_data(input_image);

    // TODO Apply the bloom filter
    // Save output image

    return 0;
}