CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I/opt/homebrew/opt/jpeg/include
LDFLAGS = -L/opt/homebrew/opt/jpeg/lib -ljpeg

bloom_filter: bloom_filter.c
		$(CC) $(CFLAGS) -o bloom_filter bloom_filter.c $(LDFLAGS)

clean:
		rm -f bloom_filter