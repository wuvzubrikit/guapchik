#ifndef ___AUX___
#define ___AUX___
//data structure
typedef struct {
	char first_name[12];
	char last_name[12];
	char gender[7];
	char occupation[15];
	unsigned salary;
} data;
//database summary
typedef struct {
	data* database;
	unsigned length;
} summary;

#define buffer_size 512

enum STATE { VALUE_START, VALUE, VALUE_END, ERROR } state;
enum FIELD { FIRST_NAME, LAST_NAME, GENDER, OCCUPATION, SALARY } field;

data* database;

summary csv_read_from_file(char* filename);
void print_histogram(data* database, unsigned n, char* category);
char format(char* str);



#endif