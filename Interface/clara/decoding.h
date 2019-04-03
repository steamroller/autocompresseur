#ifndef DECODING_H
#define DECODING_H

int is_prime_number(int n);
int PGCD(int a, int b);
long expo_modul(long a, long b, long n);
char* decoding(char str[]);
int private_key(int p, int q);

struct list
{
	struct list *next;
	char data;
};

// Initialize the sentinel of an emtpy list
void list_init(struct list *List);

// Insert an element at the beginning of the list
void list_push_end(struct list *list, char elm);

void list_free(struct list *l);


// Initialize the sentinel of an emtpy list
//void list_init(struct list *List);

// Insert an element at the beginning of the list
void list_push_endo(struct list *list, int elm);

char* list_to_char(struct list *l, int size);


#endif
