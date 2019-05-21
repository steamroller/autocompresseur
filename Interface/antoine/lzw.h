#ifndef LZW_H
#define lWW_H

struct dictionary* build();
struct dictionary* add(char* to_add,struct dictionary *dico);
size_t leng(char *s);
int are_equal(char *s1, char *s2);
int weight(char *s);
int is_belonging(struct dictionary *dico, char *s);
//int max_word(struct dictionary *dico, char *s);
void substring(char *s);
char *final(struct dictionary *dico, char *s,int *tab,int *nbw);
int digit_count(int nombre);
char *recup(struct dictionary *dic, int index);
char *first(char *s);
char *decompress(char *init,char *dest);
int nbword(char *s);
int sod(struct dictionary *dico);
char *inch(int *tab, char *dest);

#endif
