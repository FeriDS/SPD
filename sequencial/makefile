CC = gcc 
CFLAGS = -Wall -Ofast
LDFLAGS = -lm

mult_matrix_src = src/mult_matrix.c
gen_matrix_src = src/gen_matrix.c

all: mult_matrix.out gen_matrix.out
.PHONY: all clean

mult_matrix.out: $(mult_matrix_src) makefile
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

gen_matrix.out: $(gen_matrix_src) makefile
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@
clean:
	rm -f mult_matrix.out
	rm -f gen_matrix.out
