CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I/opt/homebrew/opt/jpeg/include
LDFLAGS = -L/opt/homebrew/opt/jpeg/lib -ljpeg -lm

bloom_filter: bloom_filter.c image_utils.o
	$(CC) $(CFLAGS) -o bloom_filter bloom_filter.c image_utils.o $(LDFLAGS)

image_utils.o: image_utils.c
	$(CC) $(CFLAGS) -c image_utils.c

clean:
	rm -f bloom_filter image_utils.o