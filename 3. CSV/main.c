#include "auxilary.h"

int main(int argc, char** argv) {
	
	summary input = csv_read_from_file(argv[1]);
	print_histogram(input.database, input.length, argv[2]);
	return 0;
}