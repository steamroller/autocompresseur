#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

//============================================================================
//==============================BINTREE=======================================
//============================================================================
struct bintree
{
	//int value;
	char letter;
	struct bintree *left;
	struct bintree *right;

};

//============================================================================
//==============================LISTUPLE=======================================
//============================================================================

struct listuple //STRUCTURE DES LISTES DE TUPLES
{
	int freq;
	char letter;
	struct listuple *next;
};

struct bizzare//STRUCTURE DES LISTES DE TUPLES : [(int occ, bintree *arbre)...]
{
	int occ;
	struct bintree *arbre;
	struct bizzare *next;
};

void init_listuple(struct listuple *liste) //INITIALISER UNE LISTE DE TUPLES = SENTINELLE
{
	liste->next = NULL;
	liste->letter = 'r';
	liste->freq = -1;
}

void insert(struct listuple *liste,struct listuple *elm)//INSERER DANS UNE LISTE DE TUPLES
{
	//printf("null : %i\n",liste->freq);
	struct listuple *head = liste;
	//liste = liste->next;
	//printf("ca passe\n");
	while(liste->next != NULL && (liste->next)->freq > elm->freq)
	{
		liste = liste->next;
	}
	if(liste->next == NULL)
	{
		liste->next = elm;
		elm->next = NULL;
		liste = head;
	}
	else
	{
		struct listuple *temp = liste->next;
		liste->next = elm;
		elm->next = temp;
		liste = head;
	}
	
}

int len_listuple(struct listuple *l)//LONGUEUR D'UNE LISTE DE TUPLES
{
	struct listuple *ret = l;
	int compt = 0;
	l = l->next;
	if(l == NULL)
		return 0;
	else
	{
		while(l != NULL)
		{
			compt += 1;
			l = l->next;
		}
	}
	l = ret;
	return compt;
}

char catch_letter(struct listuple *l,int index)//RECUPERE LA LETTRE A UN INDEX DONNE
{
	int size = len_listuple(l);
	l = l->next;
	if(index >= size)
		printf("prob index");
	else
	{
		int i = 0;
		while(i < index)
		{
			i += 1;
			l = l->next;
		}
		return l->letter;
	}
	return 'a';
}

int catch_occ(struct listuple *l,int index)
{
	int size = len_listuple(l);
	l = l->next;
	if(index >= size)
		printf("prob index");
	else
	{
		int i = 0;
		while(i < index)
		{
			i += 1;
			l = l->next;
		}
		return l->freq;
	}
	return -1;

}

//============================================================================
//==============================TREE_LIST=======================================
//============================================================================




int len_bizzare(struct bizzare *liste)
{
    int size = 0; 
    liste = liste->next;
    while (liste != NULL)
    {
         size++;
         liste = liste->next;
    }

    return size;
}

void pop(struct bizzare *b)
{

	struct bizzare *f = b;
	if(len_bizzare(b)==1)
		b = NULL;
	else
	{
		while(b->next->next != NULL)
		{
			b = b->next;
		}
		b->next = NULL;
		b = f;
	}
}


void init_bizzare(struct bizzare *liste)
{
    liste->next = NULL;
    liste->arbre = NULL;
    liste->occ = -1;
}

void insert2(struct bizzare *liste,struct bizzare *elm)
{
	struct bizzare *head = liste;
	//liste = liste->next;
	while(liste->next != NULL && (liste->next)->occ > elm->occ)
	{
		liste = liste->next;
	}
	if(liste->next == NULL)
	{
		liste->next = elm;
		elm->next = NULL;
		liste = head;
	}
	else
	{
		struct bizzare *temp = liste->next;
		liste->next = elm;
		elm->next = temp;
		liste = head;
	}
	
}


int recup_occ(struct bizzare *liste,int index)
{
    int size = len_bizzare(liste);
    if (index > size)
    {
        printf("erreur index catch_occ_bizzare\n");
        return -1;
    }
    liste = liste->next;
    while (index > 0 && liste != NULL)
    {
        liste = liste->next;
        index--;
    }

    return liste->occ;

}


struct bintree *recup_tree(struct bizzare*liste,int index)
{
    int size = len_bizzare(liste);
    if (index > size)
    {
        printf("erreur index catch_bintree\n");
        return NULL;
    }

    liste = liste->next;
    while (index > 0 && liste != NULL)
    {
        liste = liste->next;
        index--;
    }

    return liste->arbre;

}








int whatfreq(char *input,char m)
{
	int accu = 0;
	size_t len = strlen(input);
	for(size_t i = 0; i < len; i++)
	{
		if(input[i] == m)
			accu += 1;
	}
	return accu;
}

struct listuple *build_freq_list(char *input)
{
	struct listuple *liste = calloc(1,sizeof(struct listuple));
	init_listuple(liste);
	struct listuple *head = liste;
	size_t len = strlen(input);
	char *c = calloc(1,(len+1)*sizeof(char));
	for(size_t i = 0; i<len ;i ++)
	{
		c[i] = input[i];
		if(whatfreq(c,input[i])==1)
		{
			//printf("first\n");
			struct listuple *new = calloc(1,sizeof(struct listuple));
			new->letter = input[i];
			new->freq = whatfreq(input,input[i]);
			//printf("freq de %c = %i\n",new->letter,new->freq);
			new->next = NULL;
			insert(liste,new);
		}
	}
	return head;
}



struct bintree *build_tree(struct listuple *input)
{
	int len = len_listuple(input);
	if(len == 0)
	{
		struct bintree *empty = calloc(1,sizeof(struct bintree));
		char gt = ' ';
		empty->letter = gt;
		empty->left = NULL;
		empty->right = NULL;
		return empty;
	}
	else
	{
		struct bizzare *L = calloc(1,sizeof(struct bizzare));
		init_bizzare(L);
		for(int l = 0; l < len ;l++)
		{
			struct bintree *noeud = calloc(1,sizeof(struct bintree));
			noeud->letter = catch_letter(input,l);
			struct bizzare *tuple = calloc(1,sizeof(struct bizzare));
			tuple->occ = catch_occ(input,l);
			tuple->arbre = noeud;
			insert2(L,tuple);
		}
		int Len = len - 1;
		while(Len > 1)
		{
			struct bintree *N = calloc(1,sizeof(struct bintree));
			N->left = recup_tree(L,Len);
			N->right = recup_tree(L,Len-1);
			int som = recup_occ(L,Len) + recup_occ(L,Len-1);
			pop(L);
			pop(L);
			Len -= 1;
			struct bizzare *toadd = calloc(1,sizeof(struct bizzare));
			toadd->arbre = N;
			toadd->occ = som;
			insert2(L,toadd);
			//decroissant(L);
		}
		struct bintree *N = calloc(1,sizeof(struct bintree));
		N->left = recup_tree(L,Len);
		N->right = recup_tree(L,Len-1);
		return N;


	}
}

struct gobelin
{
	int booleen;
	char *string;
};

struct gobelin *findbinary(struct bintree *B,char c)
{
	//printf("caca\n");
	if(B==NULL)
	{
		struct gobelin *golem = calloc(1,sizeof(struct gobelin));
		char archer[1] = "";
		golem->booleen = 0;
		golem->string = archer;
		return golem;
	}
	else if(B->letter == c)
	{
		struct gobelin *golem = calloc(1,sizeof(struct gobelin));
		char archer[1] = "";
		golem->booleen = 1;
		golem->string = archer;
		return golem;

	}
	else
	{
		struct gobelin *ret = findbinary(B->left,c);
		//printf("ret->string = %s\n",ret->string);
		struct gobelin *ret2;
		struct gobelin *f = calloc(1,sizeof(struct gobelin));
		if(ret->booleen)
		{
			int z = asprintf(&(ret->string),"0%s",ret->string);
			if(z == -1)
				printf("error with asprintf");
			//struct gobelin *f = calloc(1,sizeof(struct gobelin));
			int u = asprintf(&ret->string,"%s",ret->string);
			if(u == -1)
				printf("error with asprintf");
			f->string = ret->string;
			f->booleen = ret->booleen;
			//printf("fstring =%s \n",f->string);
			return f;
		}
		else //if(ret->booleen == 0)
		{
			ret2 = findbinary(B->right,c);
			if (ret2->booleen)
			{
				int z = asprintf(&(ret2->string),"1%s",ret2->string);
				if(z == -1)
					printf("error with asprintf");
			}
			//struct gobelin *f = calloc(1,sizeof(struct gobelin));
			int z = asprintf(&(ret->string),"%s%s",ret->string,ret2->string);
			if(z == -1)
				printf("error with asprintf");
			f->string = ret->string;
			f->booleen = ret2->booleen;
			//printf("fstring =%s \n",f->string);
			return f;
		}

	}
}

char *encodedata(struct bintree *h,char *input)
{
	char *s = calloc(1,sizeof(char));
	size_t l = strlen(input);
	//printf("%i\n",l);
	for(size_t i = 0;i < l; i++)
	{
		struct gobelin *pekka; //= calloc(1,sizeof(struct gobelin));
		pekka = findbinary(h,input[i]);
		//printf("%s\n",tmp);
		int z = asprintf(&s,"%s%s",s,pekka->string);
		if(z == -1)
				printf("error with asprintf");
	}
	return s;

}

char *tobinary(int x)
{
    char *bin = "";
    int n = x;
    int len = 0;
    while (n > 0)
    {
        if (n%2 == 0)
        {
            int z = asprintf(&bin,"0%s",bin);
            if(z == -1)
				printf("error with asprintf");
		}
        else
        {
            int z = asprintf(&bin,"1%s",bin);
            if(z == -1)
				printf("error with asprintf");
		}
        n = n/2;
        len++;
    }

    while (len < 8)
    {
        int z = asprintf(&bin,"0%s",bin);
        if(z == -1)
				printf("error with asprintf");
        len++;
        //printf("%i\n",len);
    }

    return bin;
}

char *encodetree(struct bintree *tree)
{
    if (tree == NULL)
        return "";
    else if (tree->left == NULL && tree->right == NULL)
    {
        char *bin;
        //printf("%c\n",tree->letter);
        int rf = asprintf(&bin,"1%s",tobinary(tree->letter));
        if(rf == -1)
				printf("error with asprintf");
        return bin;
    }
    else
    {
        char *bin;
        int u = asprintf(&bin,"0%s",encodetree(tree->left));
        if(u == -1)
				printf("error with asprintf");
        int z = asprintf(&bin,"%s%s",bin,encodetree(tree->right));
        if(z == -1)
				printf("error with asprintf");
        //printf("%s\n\n",bin);
        return bin;
    }


}

int poww(int i)
{
	int acc = 1;
	for(int y = 0; y < i; y++)
	{
		acc *= 2;
	}
	return acc;
}

int convertb(long n)
{
    int decimalNumber = 0;
	int i = 0;
	int remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*poww(i);
        ++i;
    }
    return decimalNumber;
}

char to_int(char *s)
{
	long a = atoi(s);
	int kaka = convertb(a);
	return (char)kaka;
}

struct gobelin *tobinarybis(char *input)
{
	size_t l = strlen(input);
	size_t reste = l%8;
	size_t align = 8 - reste;
	size_t j = 0;
	char *s = calloc(1,8*sizeof(char));
	char *final = calloc(1,sizeof(char));
	for(size_t i = 0; i < l-reste;i ++)
	{
		s[j]=input[i];
		if(j == 7)
		{
			int z = asprintf(&final,"%s%c",final,(char)to_int(s));
			if(z == -1)
				printf("error with asprintf");
			j = 0;
		}
		j += 1;
	}
	for(size_t m = 0; m < align;m++)
	{
		s[m] = '0';
	}
	int meme = 0;
	for(size_t w = l - reste ; w < l ; w++)
	{
		s[align + meme] = input[w];
		meme+=1;
	}
	int z = asprintf(&final,"%s%c",final,(char)to_int(s));
	if(z == -1)
				printf("error with asprintf");
	struct gobelin *pitie = calloc(1,sizeof(struct gobelin));
	pitie->string = final;
	pitie->booleen = align;
	return pitie;


}

struct mousquetaire
{
	struct gobelin *cabane;
	struct gobelin *fut;

};

struct mousquetaire *compression(char *input)
{
	struct listuple *barbare = build_freq_list(input);
	struct bintree *chevaucheur = build_tree(barbare);
	struct gobelin *un = tobinarybis(encodedata(chevaucheur,input));
	struct gobelin *deux = tobinarybis(encodetree(chevaucheur));
	struct mousquetaire *chasseur= calloc(1,sizeof(struct mousquetaire));
	chasseur->cabane = un;
	chasseur->fut = deux;
	return chasseur;

}

// PRETTY PRINT     ===============

void printwhitespace(int x)
{
    for (int i = 0; i < x; i++)
    {
        printf(" ");
    }
    //printf("%d",x);
}

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int AllNone(struct bizzare *liste)
{
    while (liste != NULL)
    {
        if (liste->arbre != NULL)
            return 0;
        liste = liste->next;
    }

    return 1;
}

int maxlvl(struct bintree *B)
{
    if (B == NULL)
        return 0;
    return max(maxlvl(B->left),maxlvl(B->right)) +1;
}

void insert_bi(struct bizzare *liste,struct bintree *tree)
{
    struct bizzare *elm = calloc(1,sizeof(struct bizzare));
    elm->arbre = tree;
    elm->next = NULL;

    while (liste->next != NULL)
    {
        liste = liste->next;
    }

    liste->next = elm;
}


void printtreeinterval(struct bizzare *liste,int lvl,int maxlvl)
{
    int l = len_bizzare(liste);

    if (!(l == 0 || AllNone(liste)))
    {    

    int floor = maxlvl - lvl;
    //printf("floor : %d, maxlvl : %d, lvl : %d\n",floor,maxlvl,lvl);
    int endgeLines = poww(max(floor -1, 0));
    int firstSpaces = poww(floor) -1;
    int betweenSpaces = poww(floor +1) -1;
    printwhitespace(firstSpaces);

    struct bizzare *L2 = calloc(1,sizeof(struct bizzare));

    struct bizzare *ret = liste;
    ret = ret->next;
    while (ret != NULL)
    {
        if (ret->arbre != NULL)
        {
            printf("%c",ret->arbre->letter);
            insert_bi(L2,ret->arbre->left);
            insert_bi(L2,ret->arbre->right);
        }
        else
        {
            insert_bi(L2,NULL);
            insert_bi(L2,NULL);
            printf(" ");
        }
        
        printwhitespace(betweenSpaces);
        ret = ret->next;
    }
    printf("\n");

    for (int i = 1; i < endgeLines +1; i++)
    {
        for (int j = 0; j < l; j++)
        {
            //printf("a");
            printwhitespace(firstSpaces - i);

            if (recup_tree(liste,j) == NULL)
            {
                //printf("b");
                printwhitespace(endgeLines + endgeLines + i + 1);
                continue;
            }
            else if (recup_tree(liste,j)->left != NULL)
                printf("/");
            else
                printwhitespace(1);

            printwhitespace(i+i-1);

            if (recup_tree(liste,j)->right != NULL)
                printf("\\");
            else
                printwhitespace(1);
            printwhitespace(endgeLines+endgeLines - i);
        }
        printf("\n");
    }

    printtreeinterval(L2,lvl +1,maxlvl);
    }
}
void printTree(struct bintree *tree)
{
    struct bizzare *sent = calloc(1,sizeof(struct bizzare));
    struct bizzare *liste = calloc(1,sizeof(struct bizzare));
    liste->arbre = tree;
    liste->next = NULL;
    sent->next = liste;
    printtreeinterval(sent,1,maxlvl(tree));
}

//===========================================================================
//							Décompression									
//===========================================================================

char *decodedata(struct bintree *huff,char *input)
{
	int length = strlen(input);
	struct bintree *B = huff;
	int i = 0;
	char *string = calloc(1,sizeof(char));
	while(i<length)
	{
		printf("B == null ? : %i , B->letter = %i \n", B==NULL,(int)B->letter);
		while(B != NULL && (int)B->letter == 0)
		{
			if(input[i] == '0')
			{
				printf("left\n");
				B = B->left;
			}
			else
			{
				printf("ritght\n");
				B = B->right;
			}
			i+=1;
		}
		printf("b->letter = %c\n",B->letter);
		int recup = asprintf(&string,"%s%c",string,B->letter);
		if(recup == -1)
			printf("problem with asprintf\n");
		B = huff;
	}
	return string;
}

struct souris
{
	struct bintree *noeud;
	int entier;
};

struct souris *create_tree(char *input,int i, int l)
{
	struct bintree *noeud = calloc(1,sizeof(struct bintree));
	noeud->left = NULL;
	noeud->right = NULL;
	if(i < l)
	{
		if(input[i] == '0')
		{
			struct souris *s = calloc(1,sizeof(struct souris));
			s = create_tree(input,i+1,l);
			noeud->left = s->noeud;
			i = s->entier;
			if(noeud->left != NULL && input[i] == '1')
			{
				i = i+1;
				int end = i+8;
				char *bin = calloc(1,sizeof(char));
				while(i < end)
				{
					int rec = asprintf(&bin,"%s%c",bin,input[i]);
					if(rec == -1)
						printf("error with asprintf\n");
					i += 1;
				}
				char key = (char)to_int(bin);
				struct bintree *r = calloc(1,sizeof(struct bintree));
				r->letter = key;
				noeud->right = r;
			}
			else if(noeud->left !=  NULL)
			{
				struct souris *t = calloc(1,sizeof(struct souris));
				t = create_tree(input,i,l);
				noeud->right = t->noeud;
				i = t->entier;
			}
		}
		else
		{
			i = i+1;
			int end = i+8;
			char *bin = calloc(1,sizeof(char));
			while(i < end)
			{
				int rec = asprintf(&bin,"%s%c",bin,input[i]);
				if(rec == -1)
					printf("error with asprintf\n");
				i += 1;
			}
			char key = (char)to_int(bin);
			struct bintree *u = calloc(1,sizeof(struct bintree));
			u->letter = key;
			noeud = u;
		}
		struct souris *final = calloc(1,sizeof(struct souris));
		final->noeud = noeud;
		final->entier = i;
		return final;
	}
	struct souris *err = calloc(1,sizeof(struct souris));
	printf("problem of size with create tree\n");
	return err;
}

struct bintree *decode_tree(char *input)
{
	struct souris *plz = calloc(1,sizeof(struct souris));
	plz = create_tree(input,0,strlen(input));
	return plz->noeud;
}




char *frombinary(char *input,int align)
{
	int length = strlen(input);
	char *bin = calloc(1,sizeof(char));
	char *last = calloc(1,sizeof(char));
	for(int i = 0; i < length; i++)
	{
		if(i == length -1)
		{
			int x = (int)(input[i]);
			last = tobinary(x);
		}
		else
		{
			int rec = asprintf(&bin,"%s%s",bin,tobinary((int)input[i]));
			if(rec == -1)
				printf("problem with asprintf\n");
		}
	}
	if(align != 0)
	{
		int h = (int)strlen(last);
		for(int y = align; y < h; y++)
		{
			int rec = asprintf(&bin,"%s%c",bin,(int)last[y]);
			if(rec == -1)
				printf("problem with asprintf\n");
		}
	}
	return bin;
}

char *decompress(char *input, int dataalign,char *tree,int treealign)
{
	char *bindata = frombinary(input,dataalign);
	char *binT = frombinary(tree, treealign);
	struct bintree *Tree = decode_tree(binT);
	return decodedata(Tree,bindata);
}

