#include <stdlib.h>
#include "hash-map.h"

int test() {
	
	node* dict = hm_init();
	if (dict == NULL)
		return 1;
	hm_add("ru", "Russia", dict);
	hm_add("sh", "Switzerland", dict);
	hm_add("ao", "Angola", dict);
	if (hm_search("ru", "Russia", dict, 1) == NULL)
		return 2;
	hm_delete("ru", "Russia", dict);
	if (hm_search("ru", "Russia", dict, 1) != NULL)
		return 3;

	return 0;
}

int main(int argc, char** argv) {
	
	int r = test();

	node* dict = hm_read_from_file("values.txt");
	hm_print(dict);
	
	return r;
}