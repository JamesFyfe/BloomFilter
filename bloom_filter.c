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
		// TODO get width, height, num_components from input image

		int width = 3600;
		int height = 1800;
		int num_components = 3;
    // TODO Apply the bloom filter
    // Save output image
		save_output_image(image_data, output_image, width, height, num_components);
		free(image_data);
    return 0;
}