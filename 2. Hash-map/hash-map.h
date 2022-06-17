#ifndef ___HASHMAP___

#define ___HASHMAP___
//size of map (more size = less collisions)
#define size 4
//max length of input string
#define maxlen 32
//info when printing
#define infomessage "------------\n-DICTIONARY-\nKey : Value\n------------\n"
//list structure
typedef struct {
	char key[maxlen];
	char value[maxlen];
	struct node* next;
} node;

node* hm_init();
int hm_add(char* key, char* value, node* hm[]);
node* hm_search(char* key, char* value, node* hm[], unsigned mode);
int hm_delete(char* key, char* value, node* hm[]);
void hm_print(node* hm[]);
node* hm_read(const char* file);

#endif