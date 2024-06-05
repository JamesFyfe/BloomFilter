#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_utils.h"

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <input_image> <output_image> <bloom_intensity> <kernel_size> <threshold>\n", argv[0]);
        return 1;
    }

    char *input_image = argv[1];
    char *output_image = argv[2];
    float bloom_intensity = atof(argv[3]);
    int kernel_size = atoi(argv[4]);
    float threshold = atof(argv[5]);

		printf("Input image: %s\n", input_image);
    printf("Output image: %s\n", output_image);
    printf("Bloom intensity: %f\n", bloom_intensity);
    printf("Kernel size: %d\n", kernel_size);
    printf("Threshold: %f\n", threshold);

		int width, height, num_components;

    // read input image into data
		unsigned char *image_data = get_image_data(input_image, &width, &height, &num_components);
		
		if (image_data == NULL) {
			fprintf(stderr, "Failed to read input image\n");
			return 1;
		}

    int kernel_radius = kernel_size / 2;
		apply_bloom(image_data, width, height, num_components, bloom_intensity, threshold, kernel_radius);

    // Save output image
		save_output_image(image_data, output_image, width, height, num_components);
		free(image_data);
    return 0;
}