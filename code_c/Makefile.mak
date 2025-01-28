# Variables
CC = gcc
CFLAGS = -Wall

# Default rule that takes two arguments
build:
	$(CC) $(CFLAGS) $(firstword $(ARGS)) -o $(lastword $(ARGS))

# Clean rule
clean:
	rm -f $(lastword $(ARGS))

.PHONY: build clean
