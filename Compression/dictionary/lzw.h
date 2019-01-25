#ifndef LZW_H
#define lWW_H

struct dictionary* build();
struct dictionary* add(char* to_add,struct dictionary *dico);
size_t leng(char *s);
int are_equal(char *s1, char *s2);
int weight(char *s);

#endif
