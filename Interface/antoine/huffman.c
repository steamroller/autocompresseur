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
	u_int8_t booleen;
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
    while (len < 7)
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
	int l = (int)strlen(input);
	int reste = l%7;
	size_t align = 7 - reste;
	int j = 0;
	char *s = calloc(1,7*sizeof(char));
	char *final = calloc(1,sizeof(char));
	for(int i = 0; i < l-reste;i ++)
	{
		s[j]=input[i];
		if(j == 6)
		{
            // PRIIINT
           // printf("string : %s\n",s);
			// tests de merde 
			//printf("santoine === %s\n",s);
			if((int)to_int(s) == -45)
			{
				int fr = asprintf(&final,"%s%s",final,"****");
				if(fr == -1)
					printf("problem with asprintf\n");

				j = -1;
			}
			else
			{
				int z = asprintf(&final,"%s%s",final,s);
				if(z == -1)
					printf("error with asprintf");
				j = -1;
			}
		}
		j += 1;
	}
	for(size_t m = 0; m < align;m++)
	{
		s[m] = '0';
	}
	int meme = 0;
	for(int w = l - reste ; w < l ; w++)
	{
		s[align + meme] = input[w];
		meme+=1;
	}
	//printf("santoine === %s\n",s);
	if(atoi(s) == -45)
	{
		int recup = asprintf(&final,"%s%c%c%c%c",final,'*','*','*','*');
		if(recup == -1)
			printf("problem with asprintf\n");
	}
	else
	{
		int z = asprintf(&final,"%s%s",final,s);
		if(z == -1)
				printf("error with asprintf");
	}
	struct gobelin *pitie = calloc(1,sizeof(struct gobelin));
	//printf("EHOOO = %s\n",final);
	//asprintf(&final,"%c%c%c%c%c%s",'*','*','*','*','*',final);
	pitie->string = final;
	pitie->booleen = align;
	//printf("God please : %s\n",final);
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
    //printf("lenght %d, input : %s\n",length,input);
	struct bintree *B = huff;
	int i = 0;
	char *string = calloc(1,sizeof(char));
	while(i<length)
	{
		//printf("B == null ? : %i , B->letter = %i \n", B==NULL,(int)B->letter);
		while(B != NULL && (int)B->letter == 0)
		{
			if(input[i] == '0')
			{
				//printf("left\n");
				B = B->left;
			}
			else
			{
				//printf("ritght\n");
				B = B->right;
			}
			i+=1;
		}
		//printf("b->letter = %c and i : %d\n",B->letter,i);
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
	//printf("i :,%d l :%d \n",i,l);
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
				int end = i+7;
				char *bin = calloc(1,sizeof(char));
				while(i < end)
				{
					int rec = asprintf(&bin,"%s%c",bin,input[i]);
					if(rec == -1)
						printf("error with asprintf\n");
					i += 1;
				}
        //printf("binary : %s\n",bin);
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
			int end = i+7;
			char *bin = calloc(1,sizeof(char));
			while(i < end)
			{
				int rec = asprintf(&bin,"%s%c",bin,input[i]);
				if(rec == -1)
					printf("error with asprintf\n");
				i += 1;
			}
//printf("binary ; %s\n",bin);
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
	//printf("problem of size with create tree\n");
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
    //printf("input : %s, align : %d\n",input,align);
	int length = strlen(input);
    //printf("length : %d\n",length);
	char *final = calloc(1,sizeof(int));
	int i = 0;
	while(i <length -7)
	{
		int recup = asprintf(&final,"%s%c",final,input[i]);
		if(recup == -1)
			printf("problem with asprintf\n");
		i+=1;
	}
	i += align;
	for(int y = i; y < length; y++)
	{
		int recup =asprintf(&final,"%s%c",final,input[y]);
		if(recup == -1)
			printf("problem with asprintf\n");
	}

	//printf("alors bordel : %s\n",final);
	return final;


	
}

char *decompress(char *input, int dataalign,char *tree,int treealign)
{
	char *bindata = frombinary(input,dataalign);
	char *binT = frombinary(tree, treealign);
	struct bintree *Tree = decode_tree(binT);
	return decodedata(Tree,bindata);
}

//==========================================================================
//==========================================================================

void whole_comp(char *input,char *filename)
{
	//printf("sizeofint = %i\n",(int)sizeof(int));
	char *data_path;
	int recup = asprintf(&data_path,"%s%s%s","../fichiers_utilisateur/",filename,".data");
	printf("data_path = %s\n",data_path);
	if(recup == -1)
			printf("problem with asprintf\n");
	char *tree_path;
	recup = asprintf(&tree_path,"%s%s%s","../fichiers_utilisateur/",filename,".tree");
	if(recup == -1)
			printf("problem with asprintf\n");
	FILE *f1;
	f1 = fopen(data_path,"wb");
	struct mousquetaire *res = compression(input);
	int len = strlen(res->cabane->string);
	char *tamp = calloc(2,sizeof(char));
	fwrite(&res->cabane->booleen,1,1,f1);
	long datasize = 1;
	for(int i = 0; i < len; i++)
	{
		for(int y = 0 ; y < 7; y++)
		{
			int recup2 = asprintf(&tamp,"%s%c",tamp,res->cabane->string[i]);
			if(recup2 == -1)
				printf("problem with asprintf\n");
			i += 1;
		}
		i-=1;
		//printf("tamp : %s\n",tamp);
		u_int8_t c = (int)to_int(tamp);
		fwrite(&c,1,1,f1);
		tamp = "";
		datasize += 1;
	}
	printf("Taille du fichier .data : %li\n",datasize);


	fclose(f1);


	FILE *f2;
	f2 = fopen(tree_path,"wb");
	int lenbis = strlen(res->fut->string);
	char *tamp2 = calloc(2,sizeof(char));
	long treesize = 1;
	fwrite(&res->fut->booleen,1,1,f2);
	for(int i = 0; i < lenbis; i++)
	{
		for(int y = 0 ; y < 7; y++)
		{
			int c = asprintf(&tamp2,"%s%c",tamp2,res->fut->string[i]);
			if(c == -1)
			printf("problem with asprintf\n");
			i += 1;
		}
		i-=1;
		//printf("tamp2 : %s\n",tamp2);
		u_int8_t c2 = (int)to_int(tamp2);
		fwrite(&c2,1,1,f2);
		tamp2 = "";
		treesize += 1;
	}
	printf("Taille du fichier .tree : %li\n",treesize);
	fclose(f2);
	

	/*FILE *f1 = fopen(data_path,"wb");
	struct mousquetaire *res = compression(input);
	printf("wtf = %i\n",res->cabane->booleen);
	fwrite(&res->cabane->booleen,sizeof(int),1,f1);
	fclose(f1);
	FILE *f3 = fopen(data_path,"rb");
	int x;
	fread(&x,sizeof(int),1,f3);
	printf("xx = %i\n",x);
	fclose(f3);*/

	/*char *data = res->cabane->string;
	for(int i = 0; i < strlen(data) ;i++)
	{
		int cv = (int)(data[i]);
		printf("cv = %i\n",cv);
		fwrite(&cv,1,1,f1);
	}
	fclose(f1);
	FILE *f2 = fopen(tree_path,"wb");
	fwrite(&res->fut->booleen,4,1,f2);
	char *tree = res->fut->string;
	for(int i = 0; i < strlen(tree) ;i++)
	{
		int cv = (int)(tree[i]);
		fwrite(&cv,4,1,f2);
	}
	fclose(f2);*/

}

void whole_decomp(char *path)
{
	long tot = 2;
	//struct mousquetaire *dodo = calloc(1,sizeof(struct mousquetaire));
	//fwrite(&chapeau,sizeof(struct mousquetaire),1,f);
	//fprintf(f,"%i%s",chapeau->fut->booleen,chapeau->fut->string);
	//fread(dodo,sizeof(struct mousquetaire),1,f);
	//printf("coucou\n");
	char *data_path;
	char *tree_path;
	int recup;
	recup = asprintf(&data_path,"%s%s%s","../fichiers_utilisateurs",path,".data");
	if(recup == -1)
			printf("problem with asprintf\n");
	recup = asprintf(&tree_path,"%s%s%s","../fichiers_utilisateurs",path,".tree");
	if(recup == -1)
			printf("problem with asprintf\n");
	u_int8_t align_data;
	u_int8_t align_tree;
	char *data =  calloc(50000,sizeof(char));
	char *tree = calloc(50000,sizeof(char));
	FILE *f1 = fopen(data_path,"rb");
	if(fread(&align_data,1,1,f1)!=1)
		printf("problem with fread\n");
	//printf("align_data = %i\n",align_data);
	int *tab = calloc(50000,sizeof(int));
	while(fread(tab,1,1,f1) == 1)
	{
		if(tab+1 == NULL)
		{
			//printf("merd a la fin\n");
			recup = asprintf(&data,"%s%s",data,frombinary(tobinary(*tab),align_data));
			if(recup == -1)
				printf("problem with asprintf\n");
		}
		else
		{
			recup = asprintf(&data,"%s%s",data,tobinary(*tab));
			if(recup == -1)
				printf("problem with asprintf\n");
		}

		//fread(tab,1,1,f1);
		//if(*tab != 0)
			//printf("tab = %i\n",*tab);
		tab += 1;
		tot += 1;
	}
	//data = frombinary(data,align_data);
	//printf("extrait : %s\n",data);
	fclose(f1);
	//printf("chocococococco\n");

	FILE *f2 = fopen(tree_path,"rb");
	if(fread(&align_tree,1,1,f2) != 1)
		printf("problem with fread\n");
	//printf("align_tree = %i\n",align_tree);
	int *tab2 = calloc(50000,sizeof(int));
	while(fread(tab2,1,1,f2) == 1)
	{
		recup = asprintf(&tree,"%s%s",tree,tobinary(*tab2));
		if(recup == -1)
			printf("problem with asprintf\n");
		//fread(tab,1,1,f1);
		//if(*tab2 != 0)
			//printf("tab2 = %i\n",*tab2);
		tab2 += 1;
		tot += 1;
	}
	
	fclose(f2);


	/*FILE *f1 = fopen(data_path,"rb");
	printf("ftell = %li\n",ftell(f1));
	fread(&align_data,4,1,f1);
	printf("padding = %i\n",align_data);
	printf("vhbivb = %li\n",fread(data,4,1,f1));
	while(fread(data,4,1,f1)==1)
	{
		printf("lpftell = %li\n",ftell(f1));
		printf("char = %c",*data);
		continue;
	}
	fclose(f1);
	
	FILE *f2 = fopen(tree_path,"rb");
	fread(&align_tree,4,1,f2);
	while(fread(tree,4,1,f2)==1)
	{
		continue;
	}
	fclose(f2);*/




	char *terminus = decompress(data,align_data,tree,align_tree);
	printf("decompress : %s\n",terminus);
	printf("Taux de compression : %.2f%%\n",100-(float)tot*100/strlen(terminus));

}
