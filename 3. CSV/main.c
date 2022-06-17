#include "auxilary.h"

int main(int argc, char** argv) {
	summary input = csv_read(argv[1]);
	csv_print_histogram(input.database, input.length, argv[2]);
	free(input);
	return 0;
}