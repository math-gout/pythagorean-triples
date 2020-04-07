#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))

void help(char *name) {
	printf("Usage:\n\t%s -x [MAX_X] -y [MAX_Y] -o [FILENAME]\nExample:\n\t%s -x 1000 -y 1000 -o triples.txt\nOmit -o to print to stdout\n", name, name);
	exit(0);
}

int isnumber(char *ptr) {
	for (int i = 0; i < strlen(ptr); i ++)
		if (ptr[i] < '0' || ptr[i] > '9')
			return 0;
	return 1;
}

int is_perfect_square(unsigned long n) {
	unsigned long s = sqrt(n);
	if (s * s == n) return 1;
	return 0;
}

int main(int argc, char *argv[]) {
	unsigned long x_max = 1000;
	unsigned long y_max = 1000;
	char *filename = "\0";
	for (int i = 1; i < argc; i ++) {
		if (strcmp(argv[i], "-x") == 0 && i + 1 < argc) {
			if (isnumber(argv[i+1])) x_max = strtoul(argv[++i], NULL, 10);
			else help(argv[0]);
		} else if (strcmp(argv[i], "-y") == 0 && i+1 < argc) {
			if (isnumber(argv[i+1])) y_max = strtoul(argv[++i], NULL, 10);
			else help(argv[0]);
		} else if (strcmp(argv[i], "-o") == 0 && i+1 < argc) {
			filename = argv[++i];
		} else {
			help(argv[0]);
		}
	}
	
	if (x_max > y_max) SWAP(x_max, y_max);
	
	if (strcmp(filename, "stdout") && strlen(filename)) {
		FILE *f = fopen(filename, "w");
		for (unsigned long y = 1; y < y_max; y ++) {
			for (unsigned long x = 1; x < MIN(y, x_max); x ++) {
				if (is_perfect_square(x*x + y*y)) {
					fprintf(f, "%lu %lu %u\n", x, y, (unsigned)sqrt(x*x + y*y));
				}
			}
		}
		fclose(f);
	} else {
		for (unsigned long y = 1; y < y_max; y ++) {
			for (unsigned long x = 1; x < MIN(y, x_max); x ++) {
				if (is_perfect_square(x*x + y*y)) {
					printf("%lu %lu %u\n", x, y, (unsigned)sqrt(x*x + y*y));
				}
			}
		}
	}
}