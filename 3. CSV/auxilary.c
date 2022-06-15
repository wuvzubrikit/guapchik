#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "auxilary.h"

summary csv_read_from_file(char* filename) {

	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "Unable to open file \"%s\".\n", filename);
		return;
	}
	
	char buffer[buffer_size];
	//initial state
	state = VALUE_START;			
	//initial number of lines
	unsigned n = 0;	
	//array of data
	database = (data*)malloc(sizeof(data));
	if (database == NULL) {
		fprintf(stderr, "Not enough memory.\n");
		return;
	}
	memset(database, 0, sizeof(data));
	//accumulating index for string
	unsigned j = 0;

	//reading lines until the end of file
	while (!feof(f)) {
		//skipping the first info line
		fgets(buffer, buffer_size, f);
		while (fgets(buffer, buffer_size, f) != NULL) {
			
			field = FIRST_NAME;

			for (unsigned i = 0; buffer[i] != '\0'; i++) {
				
				//state machine for parsing csv file
				switch (state) {

				case VALUE_START:
					if (buffer[i] == '\"')
						state = VALUE;
					else
						state = ERROR;
					break;
				case VALUE:
					if (buffer[i] == '\"')
						state = VALUE_END;
					else {
						//defines what field to read
						switch (field) {

						case FIRST_NAME:
							database[n].first_name[j] = buffer[i];
							break;
						case LAST_NAME:
							database[n].last_name[j] = buffer[i];
							break;
						case GENDER:
							database[n].gender[j] = buffer[i];
							break;
						case OCCUPATION:
							database[n].occupation[j] = buffer[i];
							break;
						case SALARY:
							database[n].salary = database[n].salary * 10 + (buffer[i] - 48);
							break;
						}
						j++;
					}
					break;
				case VALUE_END:

					j = 0;
					field = (field + 1) % 5;

					if (buffer[i] == ',')
						state = VALUE_START;
					else if (buffer[i] == '\n') {
						//allocating memory for the new element
						state = VALUE_START;
						n++;
						database = (data*)realloc(database, (n + 1) * sizeof(data));
						if (database == NULL) {
							fprintf(stderr, "Not enough memory.\n");
							return;
						}
						memset(&database[n], 0, sizeof(data));
					}
					else
						state = ERROR;				
					break;
				case ERROR:
					fprintf(stderr, "An error has occured at line %d column %d.\n", n + 1, i + 1);
					return;
					break;
				}
			}		
		}
	}	
	summary output;
	output.database = database;
	output.length = n;
	return output;
}

//function of comparing 2 strings. prints 0 if equal, otherwise 1
int cmp(char a[], char b[]) {
	unsigned result = 0;
	for (unsigned i = 0; (a[i] != '\0') || (b[i] != '\0'); i++)
		if (a[i] != b[i]) {
			result = 1;
			break;
		}
	return result;
}

int max_salary(data* arr, unsigned n) {
	int max = 0;
	for (unsigned i = 0; i < n; i++)
		max = ((max >= arr[i].salary) ? max : arr[i].salary);
	return max;
}

//procedure of formating string (first letter is capital, others are small) to unify reading
char format(char* str) {
	for (unsigned i = 0; (str[i] != '\0'); i++) {
		if (i == 0)
			str[i] = ((str[i] - 'a' < 0) ? str[i] : str[i] - 32);
		else
			str[i] = ((str[i] - 'a' < 0) ? str[i] + 32 : str[i]);
		}
	return;
}

void print_histogram(data* database, unsigned n, char* category) {
	if (database == NULL) {
		fprintf(stderr, "Unable to load database for input.\n");
		return;
	}

	char key[20];

	format(category);

	//histogram gender/salary
	if (cmp(category, "Gender") == 0 ) {
		printf("Type the value (Male, Female): ");
		scanf("%s", key);
		format(key);

		//ammount of money per unit
		int maxsalary = max_salary(database, n);
		const int scale = 70;
		int unit =  maxsalary/scale + 1;

		//prints scale
		for (unsigned i = 0; i < 28; i++)
			printf(" ");
		printf("0");
		for (unsigned i = 0; i < scale/2 - 4; i++)
			printf("-");
		printf("%d", maxsalary /2);
		for (unsigned i = 0; i < scale/2 - 4; i++)
			printf("-");
		printf("%d\n", maxsalary);

		for (unsigned i = 0; i < n; i++) {
			if (cmp(database[i].gender, key) == 0) {
				printf("%13s %-13s ", database[i].first_name, database[i].last_name);
				for (unsigned k = 0; k < database[i].salary / unit + 1; k++) {
					printf("=");
				}
				printf("\n");
			}
		}
		return;
	}
	//histogram occupation/salary
	if (cmp(category, "Occupation") == 0) {
		printf("Type the value (Producer, Scientist, etc.): ");
		scanf("%s", key);
		format(key);

		//ammount of money per unit
		int maxsalary = max_salary(database, n);
		const int scale = 70;
		int unit = maxsalary / scale + 1;

		//prints scale
		for (unsigned i = 0; i < 28; i++)
			printf(" ");
		printf("0");
		for (unsigned i = 0; i < scale/2 - 4; i++)
			printf("-");
		printf("%d", maxsalary / 2);
		for (unsigned i = 0; i < scale/2 - 4; i++)
			printf("-");
		printf("%d\n", maxsalary);

		for (unsigned i = 0; i < n; i++) {
			if (cmp(database[i].occupation, key) == 0) {
				printf("%13s %-13s ", database[i].first_name, database[i].last_name);
				for (unsigned k = 0; k < database[i].salary / unit + 1; k++) {
					printf("=");
				}
				printf("\n");
			}
		}
		return;
	}

	fprintf(stderr, "No such category.\n");
	return;
}