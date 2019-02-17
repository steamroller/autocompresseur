#ifndef ENCRYPTION_H
#define ENCRYPTION_H

int is_prime_number(int n);
int PGCD(int a, int b);
long expo_modul(long a, long b, long n);
int read(char *chain, int len);
void encryption(char string[], int p, int q);

struct list
{
	struct list *next;
	int data;
};

// Initialize the sentinel of an emtpy list
void list_init(struct list *List);

// Insert an element at the beginning of the list
void list_push_end(struct list *list, int elm);

void print_list(struct list *l);

void list_free(struct list *l);

#endif
