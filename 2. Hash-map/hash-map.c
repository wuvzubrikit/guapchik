#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash-map.h"

unsigned hash(char *s) {
	unsigned hashval = 0;
	while (*s > 0) {
		hashval = *s + 17 * hashval;
		s++;
	}
	return hashval % size;
}

//intializing hash-map
node* hm_init() {
	node** hm = malloc(size * sizeof(node));
	if (hm == NULL) {
		fprintf(stderr, "Unable to initialize hash-map.\n");
		return NULL;
	}
	for (unsigned index = 0; index < size; index++)
		hm[index] = NULL;
	return hm;
}

int hm_add(char *key, char *value, node* hm[]) {
	unsigned index = hash(key);
	//if hm pointer is NULL, then new node is created
	if (hm[index] == NULL) {
		hm[index] = (node*)malloc(sizeof(node));
		if (hm[index] == NULL) {
			fprintf(stderr, "Unable to allocate memory.\n");
			return 1;
		}
		strcpy(hm[index]->key, key);
		strcpy(hm[index]->value, value);
		hm[index]->next = NULL;
		return 0;
	}
	//if hm pointer is not NULL, then new node is added to the existing list
	node* new = (node*)malloc(sizeof(node));
	node* current = hm[index];
	if (new == NULL) {
		fprintf(stderr, "Unable to allocate memory.\n");
		return 1;
	}
	//appending the list
	while (current->next != NULL) {
		current = current->next;
	}
	strcpy(new->key, key);
	strcpy(new->value, value);
	new->next = NULL;
	current->next = new;
	return 0;
}

node* hm_search(char* key, char* value, node* hm[], unsigned mode) {

	//if mode is 1, function searches for exact key:value pair
	if (mode == 1) {
		unsigned index = hash(key);
		if (hm[index] == NULL) {
			fprintf(stderr, "Search faillure: element doesn't exist.\n");
			return NULL;
		}
		node* current = hm[index];
		while (current != NULL) {
			if (strcmp(current->key, key) == 0 && strcmp(current->value, value) == 0)
				return current;
			else
				current = current->next;
		}
	}
	//if mode is 0, function searches for the first match of either key or value
	if (mode == 0) {
		node* current;
		unsigned index = 0;
		//searching for the first not empty element
		for (unsigned i = 0; i < size; i++) {
			if (hm[i] != NULL) {
				index = i;
				break;
			}
			if (i == size - 1) {
				fprintf(stderr, "Search faillure: hash-map is empty.\n");
				return NULL;
			}
		}
		//looking for the match through all not empty elements
		for (index; index < size; index++) {
			current = hm[index];
			if (current != NULL) {
				if (strcmp(current->key, key) == 0 || strcmp(current->value, value) == 0)
					return current;
				else
					current = current->next;
			}
			if (index == size - 1) {
				fprintf(stderr, "Search faillure: such key and value do not exist.\n");
				return NULL;
			}
		}
	}
	fprintf(stderr, "Search faillure: element doesn't exist.\n");
	return NULL;
}

int hm_delete(char* key, char* value, node* hm[]) {
	unsigned index = hash(key);

	if (hm[index] == NULL) {
		fprintf(stderr, "Delete faillure: element doesn't exist.\n");
		return 1;
	}

	node* temp = NULL;
	node* current = hm[index];
	while (current != NULL) {
		if (strcmp(current->key, key) == 0 && strcmp(current->value, value) == 0) {
			//if the first element is to be deleted, then following one (or NULL) moves to the first position
			if (temp == NULL) {
				hm[index] = current->next;
			}
			else {
				temp->next = current->next;
			}
			free(current);
			return 0;
		}
		else {
			temp = current;
			current = current->next;
		}
	};
	fprintf(stderr, "Delete faillure: element doesn't exist.\n");
	return 1;
}

void hm_print(node* hm[]) {
	printf(infomessage);
	node* link;
	for (unsigned i = 0; i < size; i++) {
		link = hm[i];
		if (link != NULL)
			do {
			printf("%s : %s\n", link->key, link->value);
			link = link->next;
			} while (link != NULL);
	}
	return;
}

node* hm_read(const char *file) {
	#define buffsize 128
	FILE* f = fopen(file, "r");
	char buffer[buffsize];
	char temp[maxlen] = { 0 };
	char key[maxlen] = { 0 };
	char value[maxlen] = { 0 };
	unsigned j;
	enum FIELD {KEY, VALUE} field;

	node* hm = hm_init();

	while (!feof(f)) {
		//skipping the first info line
		fgets(buffer, buffsize, f);
		//reading line-by-line
		while (fgets(buffer, buffsize, f) != NULL) {
			j = 0;
			field = KEY;
			for (unsigned i = 0; buffer[i] != '\0'; i++) {
				if ((buffer[i] == ':') || (buffer[i] == '\n')) {
					switch (field) {
					case KEY:
						for (unsigned k = 0; temp[k] > 0; k++)
							key[k] = temp[k];
						break;
					case VALUE:
						for (unsigned k = 0; temp[k] > 0; k++)
							value[k] = temp[k];
						break;
					}
					field = field ^ 1;
					j = 0;
					memset(temp, 0, maxlen * sizeof(char));
				}
				else {
					temp[j] = buffer[i];
					j++;
				}
			}
			hm_add(key, value, hm);
			memset(key, 0, maxlen * sizeof(char));
			memset(value, 0, maxlen * sizeof(char));
		}
	}
	fclose(f);
	return hm;
}