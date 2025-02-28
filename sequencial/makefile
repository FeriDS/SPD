CC = gcc 
CFLAGS = -Wall -Ofast
LDFLAGS = -lm

matrix_src = src/matrix.c

all: mult_matrix.out 
.PHONY: all clean

mult_matrix.out: $(matrix_src) makefile
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

clean:
	rm -f mult_matrix.out
