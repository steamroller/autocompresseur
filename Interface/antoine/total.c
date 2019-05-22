//#define _GNU_SOURCE
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<err.h>


struct double_tab
{
	u_int8_t *keep;
	u_int8_t *res;
};

struct tabint
{
	u_int8_t *tab;
	int nb;
};

u_int8_t mod1(u_int8_t arg)
{
	u_int8_t tot = 0;
	tot += (arg & 16)>>2;
	tot += (arg & 8)>>2;
	tot += (arg & 4)>>2;
	return tot;
}

//============================================================================
//=================================pour ecriture et lecture sur 9bits=========
//============================================================================

int digit_count(int nombre)
{
	if(nombre == 0)
		return 1;
	else
	{
		int res = 0;
		while(nombre > 0)
		{
			nombre = nombre/10;
			res += 1;
		}
		return res;
	}
}

struct tabint *neufbits(int *tab,int nbw)
{
	int index = 0;
	u_int8_t *ret = calloc(1,(nbw * sizeof(u_int8_t))/4 + 1);
	u_int8_t *bis = ret;
	int m = 0;
	while(m<nbw)//pour tous les nombres
	{
		while(m<nbw && index < 8)//on occupe tous les bits
		{
			u_int8_t reste = (*tab & (1<<8))>>8;//= 1 ou 0
			//printf("r = %i\n",reste);
			int masque = reste << (7-index);
			//printf("masque = %i\n",masque);
			*ret = *ret | masque;
			tab += 1;
			index += 1;
			m+=1;
		}
		//printf("ret = %i\n",*ret);
		index = 0;
		ret += 1;
	}
	struct tabint *f = calloc(1,sizeof(struct tabint));
	f->tab = bis;
	f->nb = nbw;
	return f;
}

//FONCTION PRINCIPALE
struct double_tab *build_neuf(int *tab,int nbw,char *filename)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/8 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = neufbits(tabtab,nbw);
	r = tmp->tab;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;
	char *one = calloc(1,sizeof(char));
	char *two = calloc(1,sizeof(char));
	asprintf(&one,"%s.bin1",filename);
	asprintf(&two,"%s.bin2",filename);

	FILE *f1;
	f1 = fopen(one,"wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen(two,"wb");
	for(int i = 0; i < nbw/8 + 1*(nbw%8 != 0);i++)
	{
		fwrite(&(*r),1,1,f2);
		r += 1;
	}
	fclose(f2);




	return final;


}

int *recup9(char *datapath,char *datapath2)
{
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("close = %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	FILE *fp =fopen(datapath2,"rb");
	u_int8_t d = 0;
	while(fread(&d,1,1,fp)==1)
	{
		//printf("good = %i\n",d);
		for(int i = 0 ; i < 8 ; i++)
		{
			//printf("mask = %i\n",(d & (1<<(7-i)))<<i);
			*somme2 += (d & (1<<(7-i)))<<(i+1);
			somme2 += 1;
		}
	}
	//*somme2 = -1;
	fclose(fp);
	int *fou = calloc(1,(nbit*8 + 10)*sizeof(int));
	int *fouret = fou;
	int o = 0;
	while(o < nbit)//*sommef != -1)
	{
		//printf("that fuckinh sommed is : %i\n",*sommef);
		*fou = *sommef;
		fou += 1;
		sommef += 1;
		o+=1;
	}
	*fou = -1;
	return fouret;
}



//============================================================================
//================================Pour ecriture et lecture sur 10bits=========
//============================================================================

struct tabint *dixbits(int *tab,int nbw)
{
	int index = 0;
	u_int8_t *ret = calloc(1,(nbw * sizeof(u_int8_t))/2 + 1);
	u_int8_t *bis = ret;
	int m = 0;
	while(m<nbw)//pour tous les nombres
	{
		while(m<nbw && index < 8)//on occupe tous les bits
		{
			u_int8_t reste = 0b0000;
			if(*tab > 767)//si les deux bits supplementaires sont à 1
			{
				reste = 0b0011;
			}
			else if(*tab >= 512)//si le bit le plus fort est a 1 et le 9 à 0
			{
				reste = 0b0010;
			}
			else if(*tab >= 256)//si le plus fort est a 0 mais le 9 à 1
			{
				reste = 0b0001;
			}
			else//si les deux sont à 0
			{
				reste = 0b0000;
			}

			//u_int8_t reste = (*tab & (1<<8))>>8;//= 1 ou 0
			//printf("tab = %i, r = %i\n",*tab,reste);
			int masque = reste << (6-index);
			//printf("masque = %i\n",masque);
			*ret = *ret | masque;
			tab += 1;
			index += 2;
			m+=1;
		}
		//printf("ret = %i\n",*ret);
		index = 0;
		ret += 1;
	}
	struct tabint *f = calloc(1,sizeof(struct tabint));
	f->tab = bis;
	f->nb = nbw;
	return f;
}


//FONCTION PRINCIPALE
struct double_tab *build_dix(int *tab,int nbw,char *filename)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/4 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = dixbits(tabtab,nbw);
	r = tmp->tab;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;
	
	char *one = calloc(1,sizeof(char));
	char *two = calloc(1,sizeof(char));
	asprintf(&one,"%s.bin1",filename);
	asprintf(&two,"%s.bin2",filename);

	FILE *f1;
	f1 = fopen(one,"wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen(two,"wb");
	for(int i = 0; i < nbw/4 + 1*(nbw%8 != 0);i++)
	{
		fwrite(&(*r),1,1,f2);
		r += 1;
	}
	fclose(f2);




	return final;


}

int *recup10(char *datapath,char *datapath2)
{
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("close = %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	FILE *fp =fopen(datapath2,"rb");
	u_int8_t d = 0;
	while(fread(&d,1,1,fp)==1)
	{
		//printf("good = %i\n",d);
		for(int i = 0 ; i < 4 ; i++)
		{
			//printf("mask = %i\n",(d & (1<<(7-i)))<<i);
			u_int8_t v = 0b0011;
			*somme2 += (d & (v<<(6-i*2)))<<(i*2+2);
			somme2 += 1;
		}
	}
	*somme2 = -1;
	fclose(fp);
	int *fou = calloc(1,(nbit*8 + 10) * sizeof(int));
	int *fouret = fou;
	int o = 0;
	while(o < nbit)//*sommef != -1)
	{
		//printf("that fuckinh sommed is : %i\n",*sommef);
		*fou = *sommef;
		fou += 1;
		sommef += 1;
		o+=1;
	}
	*fou = -1;
	return fouret;
}


//============================================================================
//=================================pour ecriture et lecture sur 11bits=========
//============================================================================

struct tabint *onzebits(int *tab,int nbw)
{
	int index = 0;
	u_int8_t *ret = calloc(1,(nbw * sizeof(u_int8_t))/2 + 1);
	u_int8_t *bis = ret;
	int m = 0;
	int it = 1;
	while(m<nbw)//pour tous les nombres
	{
		while(m<nbw && index < 8)//on occupe tous les bits
		{
			u_int8_t reste = *tab>>8;
			//printf("tab = %i\n",*tab);
			//printf("r = %i\n",reste);
			if(m%8 == 0)
			{
				*ret = *ret | (reste<<5);
				//printf("retf = %i\n",*ret);
			}
			else if(m%8 == 1)
			{
				*ret = *ret | (reste<<2);
			}
			else if(m%8 == 2)
			{
				u_int8_t gauche = reste>>1;
				u_int8_t droite = reste % 2;
				*ret = *ret | gauche;
				//printf("ret = %i\n",*ret);
				ret += 1;
				it += 1;
				*ret = *ret | (droite<<7);
			}
			else if(m%8 == 3)
			{
				*ret = *ret | (reste<<4);
			}
			else if(m%8 == 4)
			{
				*ret = *ret | (reste<<1);
			}
			else if(m%8 == 5)
			{
				u_int8_t gauche = reste & 4;
				u_int8_t droite = reste & 3;
				*ret = *ret | (gauche);
				//printf("ret = %i\n",*ret);
				ret += 1;
				it += 1;
				*ret = *ret | (droite<<6);
			}
			else if(m%8 == 6)
			{
				*ret = *ret | (reste<<3);
			}
			else if(m%8 == 7)
			{
				*ret = *ret | (reste);
				//printf("retf = %i\n",*ret);
				ret += 1;
				if(m+1<nbw)
					it+=1;
			}
			m+=1;
			tab += 1;
			//printf("ret = %i\n",*ret);

		}
		//printf("ret = %i\n",*ret);
	}
	struct tabint *f = calloc(1,sizeof(struct tabint));
	f->tab = bis;
	//printf("nbitnec = %i\n",it);
	f->nb = it;
	return f;
}

//FONCTION PRINCIPALE
struct double_tab *build_onze(int *tab,int nbw, char *filename)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/2 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = onzebits(tabtab,nbw);
	r = tmp->tab;
	int it = tmp->nb;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;
	
	char *one = calloc(1,sizeof(char));
	char *two = calloc(1,sizeof(char));
	asprintf(&one,"%s.bin1",filename);
	asprintf(&two,"%s.bin2",filename);

	FILE *f1;
	f1 = fopen(one,"wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen(two,"wb");
	for(int i = 0; i < it;i++)
	{
		//printf("writtenr = %i\n",*r);
		fwrite(&(*r),1,1,f2);
		r += 1;
	}
	fclose(f2);




	return final;


}

int *recup11(char *datapath,char *datapath2)
{
	int *somme = calloc(1,1000000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	int m = 0;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("sur 8bits = %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	FILE *fp =fopen(datapath2,"rb");
	u_int8_t d = 0;
	int a = 1;
	int joker = 0;
	int jokerbis = 0;
	while(fread(&d,1,1,fp)==1)
	{
		//printf("lus = %i\n",d);
		while(a)
		{
			if(m%8 == 0)
			{
				//printf("somme init= %i\n",*somme2);
				//printf("d = %i\n",d);
				*somme2 += ((d>>5)<<8);
				//printf("dodo = %i\n",*somme2);
				somme2 += 1;
				m+=1;
			}
			else if(m%8 == 1)
			{
				//printf("congru a 1\n");
				*somme2 += (mod1(d)<<8);
				somme2 += 1;
				m+=1;
			
			}
			else if(m%8 == 2)
			{
				if(joker == 0)
				{
					//printf("congru a 2,1\n");
					int b = 0b0011;
					*somme2 += ((d & b)<<9);
					a = 0;
					joker = 1;
				}
				else
				{
					//printf("congru a 2,2\n");
					*somme2 += ((d & 128)<<1);
					joker = 0;
					somme2 += 1;
					m+=1;
				}
			}
			else if(m%8 == 3)
			{
				//printf("congru a 3\n");
				int mask = 0b01110000;
				*somme2 += ((d&mask)<<4);
				somme2 += 1;
				m+=1;
			}
			else if(m%8 == 4)
			{
				//printf("congru a 4\n");
				int mask = 0b00001110;
				*somme2 += ((d&mask)<<7);
				somme2 += 1;
				m+=1;
			}
			else if(m%8 == 5)
			{
				if(jokerbis == 0)
				{
					//printf("congru a 5,1\n");
					*somme2 += ((d & 1)<<10);
					a = 0;
					jokerbis = 1;
				}
				else
				{
					//printf("congru a 5,2\n");
					int n = 0b11000000;
					*somme2 += ((d & n)<<2);
					jokerbis = 0;
					somme2 += 1;
					m+=1;
				}
			}
			else if(m%8 == 6)
			{
				//printf("congru a 6\n");
				int mask = 0b00111000;
				*somme2+= ((d&mask)<<5);
				somme2 += 1;
				m+=1;
			}
			else if(m%8 == 7)
			{
				//printf("congru a 7\n");
				int mask = 0b00000111;
				*somme2+= ((d&mask)<<8);
				somme2 += 1;
				a=0;
				m+=1;
			}
		}
		a=1;
	}
	*somme2 = -1;
	fclose(fp);
	int *fou = calloc(1,(nbit*8 + 10) * sizeof(int));
	int *fouret = fou;
	int o = 0;
	while(o < nbit)//*sommef != -1)
	{
		printf("that fuckinh sommed is : %i\n",*sommef);
		*fou = *sommef;
		fou += 1;
		sommef += 1;
		o+=1;
	}
	*fou = -1;
	return fouret;
}



//===========================================================================
//===============================Ecriture et lecture sur 12 bits=============
//===========================================================================
struct tabint *douzebits(int *tab,int nbw)
{
	int index = 0;
	u_int8_t *ret = calloc(1,(nbw * sizeof(u_int8_t))/2 + 1);
	u_int8_t *bis = ret;
	int m = 0;
	while(m<nbw)//pour tous les nombres
	{
		while(m<nbw && index < 8)//on occupe tous les bits
		{
			u_int8_t reste = (*tab>>8);//= 1 ou 0
			//printf("squelette = %i\n",reste);
			int masque = reste << (4-index);
			//printf("masque = %i\n",masque);
			*ret = *ret | masque;
			tab += 1;
			index += 4;
			m+=1;
		}
		//printf("ret = %i\n",*ret);
		index = 0;
		ret += 1;
	}
	struct tabint *f = calloc(1,sizeof(struct tabint));
	f->tab = bis;
	f->nb = nbw;
	return f;
}

//FONCTION PRINCIPALE
struct double_tab *build_douze(int *tab,int nbw,char *filename)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/8 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = douzebits(tabtab,nbw);
	r = tmp->tab;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;
	
	char *one = calloc(1,sizeof(char));
	char *two = calloc(1,sizeof(char));
	asprintf(&one,"%s.bin1",filename);
	asprintf(&two,"%s.bin2",filename);

	FILE *f1;
	f1 = fopen(one,"wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);

	FILE *f2;
	f2 = fopen(two,"wb");
	for(int i = 0; i < nbw/2 + 1*(nbw%8 != 0);i++)
	{
		fwrite(&(*r),1,1,f2);
		r += 1;
	}
	fclose(f2);




	return final;


}

int *recup12(char *datapath,char *datapath2)
{
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("avantdernier= %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	FILE *fp =fopen(datapath2,"rb");
	u_int8_t d = 0;
	while(fread(&d,1,1,fp)==1)
	{
		//printf("good = %i\n",d);
		for(int i = 0 ; i < 8 ; i++)
		{
			//printf("mask = %i\n",(d & (1<<(7-i)))<<i);
			if(i == 0)
			{
				*somme2 += ((d & 240)<<4);
			}
			else
			{
				*somme2 += ((d&15)<<8);
			}
			i+=4;
			somme2 += 1;
		}
	}
	*somme2 = -1;
	int *fou = calloc(1,(nbit* 8 + 10) * sizeof(int));
	int *fouret = fou;
	int o = 0;
	while(o < nbit)//*sommef != -1)
	{
		//printf("that fuckinh sommed is : %i\n",*sommef);
		*fou = *sommef;
		fou += 1;
		sommef += 1;
		o+=1;
	}
	*fou = -1;
	return fouret;
}

//============================================================================
//=================================pour ecriture et lecture sur 8bits=========
//============================================================================

//FONCTION PRINCIPALE
struct double_tab *build_huit(int *tab,int nbw,char *filename)
{
	u_int8_t *k = calloc(1,nbw*sizeof(u_int8_t));
	u_int8_t *kk = k;
	int *tabtab =tab;
	u_int8_t *r = calloc(1,(nbw/8 + 1*(nbw%8 != 0))*sizeof(u_int8_t));
	for(int i = 0; i < nbw;i++)
	{
		*k = *tab & 255;
		k += 1;
		tab += 1;
	}
	struct tabint *tmp = neufbits(tabtab,nbw);
	r = tmp->tab;

	struct double_tab *final = calloc(1,sizeof(struct double_tab));
	final->keep = kk;
	final->res = r;
	char *one = calloc(1,sizeof(char));
	char *two = calloc(1,sizeof(char));
	asprintf(&one,"%s.bin1",filename);
	asprintf(&two,"%s.bin2",filename);

	FILE *f1;
	f1 = fopen(one,"wb");
	for(int i = 0; i < nbw;i++)
	{
		fwrite(&(*kk),1,1,f1);
		kk += 1;
	}
	fclose(f1);
	FILE *f2;
	f2 = fopen(two,"wb");
	fclose(f2);




	return final;


}

int *recup8(char *datapath,char *datapath2)
{
	(void)datapath2;
	int *somme = calloc(1,10000*sizeof(int));
	int *somme2 = somme;
	int *sommef = somme;
	FILE *f =fopen(datapath,"rb");
	int nbit = 0;
	u_int8_t p = 0;
	while(fread(&p,1,1,f)==1)
	{
		//printf("close = %i\n",p);
		*somme = p;
		somme += 1;
		nbit += 1;
	}
	fclose(f);


	//char *fou = calloc(1,sizeof(char));
	int *fou = calloc(1,(nbit*8 + 10)*sizeof(int));
	int *fouret = fou;
	int o = 0;
	while(o < nbit)//*sommef != -1)
	{
		//printf("that fuckinh sommed is : %i\n",*sommef);
		*fou = *sommef;
		//printf("fou = %i\n",*fou);
		fou += 1;
		sommef += 1;
		o+=1;
	}
	(void)somme2;
	*fou = -1;
	/*for(int m = 0 ; m<10 ; m++)
	{
		printf("m = %i\n",*fouret);
		fouret += 1;
	}*/
	return fouret;
}





/*int main(int argc,char *argv[])
{
	//int a = 500;
	int masque = 255;
	int reste = (a & (1<<8))>>8;
	printf("a = %i et reste = %i\n",a & masque,reste);

	int rec = (reste << 8) + (a & masque) ;
	printf("so = %i\n",rec);
	//int arg = atoi(argv[1]);
	//printf("res = %i\n",arg & 255);
	int tab[17]={4090,956,350,350,129,256,12,15,1020,899,350,350,129,256,12,15,1003};*/
	/*struct tabint *test = neufbits(tab,16);
	for(int u = 0;u<2;u++)
	{
		printf("reste = %i\n",*test->tab);
		test->tab += 1;
	}*/
////////
	/*struct double_tab *main = build_douze(tab,17);
	for(int u = 0; u < 17 ;u++)
	{
		printf("keep n-%i = %i\n",u,*(main->keep));
		main->keep+=1;
	}
	for(int p = 0; p < 2;p++)
	{
		printf("reste n-%i = %i\n",p,*(main->res));
		main->res += 1;

	}
	char *print = calloc(1,sizeof(char));
	int u = asprintf(&print,"%s%s",print,recup12("test.bin","testb.bin"));
	printf("%s\n",print);
	///////

	printf("test de lerde  = %i\n",mod1(111));
	//recup("test.bin","testb.bin");
	//dixbits(tab,15);

}*/

//LZWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
struct dictionary
{
	char *value;
	struct dictionary *next;
	int num;
};

int nbword(char *s)
{
	size_t p = strlen(s);
	size_t i = 0;
	int cpt =  0;
	while(i < p)
	{
		if(s[i]=='<')
			cpt += 1;
		i+=1;
	}
	return cpt;
}


char *convert(int q)
{
	char *t = calloc(1,sizeof(char));

	if(digit_count(q)==1)
	{
		int a = asprintf(&t,"%c%c%i",'0','0',q);
		if (a == -1)
			printf("error");
		return t;
	}
	if(digit_count(q)==2)
	{
		int a = asprintf(&t,"%c%i",'0',q);
		if (a == -1)
			printf("error");
			
		return t;
	}
	else
	{
		int a = asprintf(&t,"%i",q);
		if (a == -1)
			printf("error");
	}
		
	return t;
}









void substring(char *s)
{
	size_t len = strlen(s);
	s[len-1] = 0;
}


//Function that tells if two strings are equals or not
int are_equal(char* s1, char* s2)
{
	return strcmp(s1,s2);
}

//Function returning the ascii's weight of a string
int weight(char *s)
{
	size_t i = strlen(s);
	int u = 0;
	for(size_t p = 0; p < i; p++)
	{
		u += (int)(s[p]);
	}
	return u;
}

int is_belonging(struct dictionary *dico, char *s)
{
	//printf("pas d'abandon\n");
	int w = weight(s);
	//struct dictionary *f = dico;
	int index = 0;
	while(dico->next != NULL)
	{
		if(dico->num == w && strcmp(dico->value,s)==0)
		{
			return index;
		}
		index += 1;
		dico = dico->next;
	}
	if(strcmp(dico->value,s)==0)
	{
		return index;
	}
	return -1;
}






//Function that initializes a dictionary only with the ascii table(128)
struct dictionary *build()
{
	struct dictionary *dico = calloc(1,sizeof(struct dictionary));
	struct dictionary *un = dico;;
	for(size_t i = 0; i<128; i++)
	{
		if(dico == NULL)
			printf("capi\n");
		char *str = malloc(2*sizeof(char));
		str[1] = 0;
		*str = (char)i;
		(dico->value) = (char*)str;
		dico -> num = (int)(weight(str));
		if(i<127)
		{
			dico->next = calloc(1,sizeof(struct dictionary));
			dico = dico->next;
		}
	}
	dico->next = NULL;
	return un;

}

//Fuction that add a new sequence in the dictionary
struct dictionary *add(char* to_add,struct dictionary *dico)
{

	struct dictionary *final = dico;
	//size_t l = strlen(to_add);
	//int w = weight(to_add);
	//printf("to_add's weight = %i\n",w);
	//printf("to_add = %s \n",(to_add));
	struct dictionary *new = malloc(1*sizeof(struct dictionary));
	/*char *str = malloc(2*sizeof(char));
	for(size_t y = 0;y < l; y++)
	{
		*str = *to_add;
		str += 1;
		to_add += 1;
	}
	str-= l;
	new->value = (char*)str;*/
	new->value = to_add;
	while(dico->next != NULL)
	{
		dico = dico->next;
	}
	dico->next = new;
	//new->num = (int)(weight(str));
	new->num = (int)(weight(to_add));
	new->next = NULL;
	return final;
}



//======================================================================================================================================================================
																																										
																																										
//																COMPRESSION																								
																																										
																																										
//======================================================================================================================================================================

struct arya
{
	int nbww;
	char *chaine;
};

struct arya *max_word(struct dictionary *dico, char*s,char *str,int nbw,int *tab)
{
	if(*s == 0)
	{
		nbw = nbw;
		tab-=nbw;
		//return str;
		struct arya *r = calloc(1,sizeof(struct arya));
		r->nbww = nbw;
		r->chaine = str;
		return r;

	}
	if(strlen(s) == 1)
	{
		*tab = is_belonging(dico,s);
		//printf("*tab = %i\n",*tab);
		int a = asprintf(&str,"%s<%d>",str,is_belonging(dico,s));
		if (a == -1)
			printf("error");
		nbw = nbw;
		//*(tab+1) = -1;
		tab -= nbw;
		//printf("*f = %i\n",*tab);
		//printf("nbw = %i\n",nbw);
		struct arya *r = calloc(1,sizeof(struct arya));
		r->nbww = nbw;
		r->chaine = str;
		return r;
	}
	else
	{
		struct dictionary *f = dico;
		int size = 1;
		char *toreturn = calloc(1,1000*sizeof(char));
		*toreturn = *s;
		toreturn += 1;
		s += 1;
		char *temp = toreturn-size;
		while(*s != 0 && is_belonging(dico,temp)!= -1)
		{
			*toreturn = *s;
			s+=1;
			toreturn += 1;
			size += 1;
			temp = toreturn - size;
		}

		//printf("par ici : %s\n",temp);
		int a;
		if((a = is_belonging(dico,temp))!=-1)
		{
			//printf("pas de chance = %i\n",a);
			*tab = a;
			//printf("*tab = %i\n",*tab);
			int b = asprintf(&str,"%s<%s>",str,convert(a));
			if (b == -1)
				printf("error");
			dico = f;
			nbw = nbw;
			//*(tab+1) = -1;
			tab -= nbw;
			//printf("*f = %i\n",*tab);
			//printf("nbw = %i\n",nbw);

			//return str;
			struct arya *r = calloc(1,sizeof(struct arya));
			r->nbww = nbw;
			r->chaine = str;
			return r;

		}
		

		
		//substring(temp);
		//printf("we add = %s\n",temp);
		//char *chiffre = (substring(temp,1));
		char *chiffre = temp;
		char last = chiffre[strlen(chiffre)-1];
		substring(chiffre);
		char *chiffree = calloc(1,1000*sizeof(char));
		//printf(" = %s\n",chiffre);
		for(size_t i = 0; i<strlen(chiffre);i++)
		{
			chiffree[i]=chiffre[i];
		}
		temp[strlen(chiffre)]= last;
		temp[strlen(chiffre)] = 0;
		//printf("we add = %s\n",temp);
		//printf("we write = %s\n",chiffree);
		int vg  = is_belonging(dico, chiffree);
		//printf("vg = %i\n",vg);
		dico = f;
		dico = add(temp,dico);
		dico = f;
		s -= 1;
		*tab = vg;
		printf("*tab = %i\n",*tab);
		tab += 1;
		int c = asprintf(&str,"%s<%s>",str,convert(vg));
		if (c == -1)
			printf("error");
		return max_word(dico,s,str,nbw+1,tab);
	}
}

/*char *max_word(struct dictionary *dico,char *s,int i, char *str)
{
	if(s[i] == 0)
	{
		return str;
	}
	else
	{
		size_t u = 2;//nb caracteres
		char *tmp = calloc(1,u*sizeof(char));
		tmp[0]=s[i];
		while(s->next != NULL && is_blonging(dico,tmp)!=-1)
		{
			i+=1;
			tmp = realloc(tmp,(u+1)*sizeof(char));
			tmp[i]=s[i];
		}
	}
}*/


char *final(struct dictionary *dico, char *s,int *tab,int *nbw)
{
	//printf("taille = %i\n",sod(dico));
	char *v = calloc(1,8000*sizeof(char));
	int a = 1;
	struct arya *ret = max_word(dico,s,v,a,tab);
	//printf("a = %i\n",ret->nbww);
	*nbw = ret->nbww;
	return ret->chaine;
}

//======================================================================================================================================================================
																																										
																																										
//																DECOMPRESSION																							
																																										
																																										
//======================================================================================================================================================================

int sod(struct dictionary *dico)
{
	int retour = 0;
	while(dico != NULL)
	{
		retour += 1;
		dico = dico->next;
	}
	return retour;
}

char *recup(struct dictionary *dic, int index)
{
	//printf("index = %i\n",index);
	if(index >= sod(dic))
		printf("tentative de recuperer un valeur superieur à la taille du dico");
	int s = 0;
	//printf("graille\n");
	struct dictionary *f = dic;
	//printf("steak\n");
	while(s != index)
	{
		//printf("fanta");
		dic = dic->next;
		s += 1;
	}
	//printf("germain le mais humain\n");
	//size_t t = strlen(dic->value);
	//printf("t = %li\n",t);
	char *ret = calloc(1,10*sizeof(char));
	//printf("la\n");
	//printf("val = %s\n",dic->value);
	int a = asprintf(&ret,"%s%s",ret,dic->value);
	//printf("back\n");
	if (a == -1)
		printf("error");
	//printf(" si ca s'affiche j'y vais\n");
	dic = f;
	//printf("pcq la c bon \n");
	return ret;
}





char *first(char *s)
{
	//printf("sos");
	size_t taille = strlen(s);
	int i = 0;
	if(*s == '>'&& taille > 1)
		s+= 1;
	if(*s == '<')
		s += 1;
	//printf("ddd");
	char *ret = calloc(1,4*sizeof(char));
	while(s[i]!='>')
	{
		//printf("first = %c \n",*s);
		ret[i] = s[i];
		i += 1;
	}
	return ret;
	
}

char *decompresss(char *init,char *dest)
{
	struct dictionary *dico = calloc(1,sizeof(struct dictionary));
	dico = build();
	size_t i = 0;
	size_t tot = strlen(init);
	int index = 0;
	while(i < tot-1)
	{
		//bw += 1;
		int b = 0;
		if(init[i] == '<')
			i += 1;
		size_t s = 0;
		char *temp = calloc(1,10*sizeof(char));

		while(init[i] != '>')
		{
			temp[s] = init[i];
			i += 1;
			s += 1;
		}
		//printf("tmp %i = %s\n",index,temp);
		index += 1;
		int actu = atoi(temp);
		//if(tp < sod(dico))
		if(1)
		{
			//printf("potatoes\n");
			int a = asprintf(&dest,"%s%s",dest,recup(dico,actu));
			if (a == -1)
				printf("error");
			//printf("so?\n");
			char *temporary;
			//printf("init = %s\n",init);
			int next ;
			if (i<tot-4)
				next = atoi(first(init + i + 1));
			else
				next = 5;//CRAEFUL
			//printf("I = %i\n",i);
			//printf("as suposed, tpn = %i\n",next);
			//printf(" i = %i\n",i);
			//printf("actu = %i et next = %i sachant que le dico a %i cases\n",actu,next,sod(dico));

			if(i<tot-1 && next >= sod(dico))
			{
				//printf("c ca hein \n");
				char *casse = calloc(1,6*sizeof(char));
				a = asprintf(&casse,"%s%c",recup(dico,actu),recup(dico,actu)[0]);
				if (a == -1)
					printf("error");
				add(casse,dico);
				b = 1;
				//printf("b = 1\n");
			}


			if(b == 0 && i< tot -1)
			{
				int a = asprintf(&temporary,"%s%c",recup(dico,actu),recup(dico,next)[0]);
				if (a == -1)
					printf("error");
			}
			//printf("added = %s\n",temporary);
			//printf("here\n");
			if(i< tot -1 && b == 0 && is_belonging(dico,temporary)==-1)
			{
				//printf("addedd = %s\n",temporary);
				add(temporary,dico);
			}
			//i += digit_count(tpn);
			//printf("i = %i\n",i);
			//free(temp);
			i += 2;
			//printf(" ii = %i\n",i);
			//printf("result = %s\n",dest);
			//printf("bw = %i\n",bw);
		}

		
		//printf("bw = %i\n",bw);
		

	}
	//printf("bw = %i\n",bw);
	return dest;



}

char *inch(int *tab,char *dest)
{
	//printf("probably memory if not here\n");
	int *bis = NULL;
	bis = tab;
	int *tri = tab;
	/*for(int o = 0 ; o < 10 ;o++)
	{
		printf("crocodule = %i\n",*tab);
		tab += 1;
	}*/
	//printf("inchishere\n");
	//struct dictionary *dico = build();
	int brico = 0;
	while(*tri != -1)
	{
		//printf("u = %i\n",*tri);
		tri += 1;
		brico += 1;
	}
	tri -= brico;
	struct dictionary *dico = build();
	struct dictionary *last = dico;

	//printf("ehe\n");
	int si = 128;
	char *prev = calloc(1,15*sizeof(char));
	//printf("ehaeho\n");
	char *too = calloc(1,15*sizeof(char));
	/*if(prev == NULL || too == NULL)
		printf("dead\n");*/
	//printf("eho\n");
	int test = 0;
	//while(*bis != -1)
	while(test < brico)
	{
		test += 1;
		/*for(int u = 0 ; u < 10 ;u++)
		{
			printf("u = %i\n",*tri);
			tri += 1;
		}
		tri -= 10;*/
		//printf("dest = %s\n",dest);
		//printf("bis = %i\n",*bis);
		//printf("bis+1 = %i\n",*(bis+1));
		if(*bis < si)
		{
			//printf("va dej\n");
			int res = asprintf(&dest,"%s%s",dest, recup(dico, *bis));
			//printf("dest = %s\n",dest);
			//printf("masi wtfff\n");
			if(res == -1)
				printf("preob\n");
			too = "";
			int y = asprintf(&too, "%s%s%c",too,prev,(recup(dico,*bis))[0]);
			if(y == -1)
				printf("preob\n");
		//	printf("porte\n");
			if(is_belonging(dico,too)==-1)
			{
				//printf("choco\n");
				add(too,dico);
				//printf("too = %s\n",too);
				si += 1;
			}
			//printf("pronblaime\n");
			prev = recup(dico,*bis);
			//printf("chealsez\n");
		}
		else
		{
			//printf("even that\n");
			too = "";
			int j = asprintf(&dest,"%s%s%c",dest,prev,prev[0]);
			int k = asprintf(&too,"%s%s%c",too,prev,prev[0]);
			if(k == -1 || j == -1)
				printf("probb with asprintf\n");
			add(too,dico);
			prev =too;
			si += 1;
		}
		bis = bis + 1;
	}
	/*int x = 0;
	for(int m = 0 ; m < 169 ; m++)
	{
		printf("dico[%i] = %s\n",m,last->value);
		last = last->next;
	}*/
	(void)last;

	return dest;
}
///////////////////////////FINADJKBNEJIBOVHLVFVFINAL
long size(char *adrr)
{
	FILE *f;
	long size = 0;
	f = fopen(adrr,"rb");
	if(f)
	{
		fseek(f,0,SEEK_END);
		size = ftell(f);
		fclose(f);
		//printf("done\n");
		return size;
	}
	return -1;
}

/*struct double_tab
{
	u_int8_t *keep;
	u_int8_t *res;
};*/

/*struct tabint
{
	u_int8_t *tab;
	int nb;
};*/

void printab(int *tab)
{
	printf("chips\n");
	printf("%i\n",*tab);
	//int taille = sizeof(tab)/sizeof(int);
	//int i = 0;
	while(*tab != -1)
	{
		printf("kcbeoi\n");
		printf("%i\n",*tab);
		tab += 1;
	}
}


int sod(struct dictionary *dico);

//int *tab = calloc(1000,sizeof(int));




int powww(int i)
{
	int acc = 1;
	for(int y = 0; y < i; y++)
	{
		acc *= 2;
	}
	return acc;

}
int nec(int nb)
{
	int i = 8;
	while(powww(i)<nb)
	{
		i += 1;
	}
	return i;

}
char *to_ascii(char *nul)
{
	char *res = calloc(1,strlen(nul)*sizeof(char));
	char *bis = res;
	int taille = strlen(nul);
	for(int i = 0 ; i < taille ; i++)
	{
		if (nul[i] == -30)
		{
			*res = (char)39;
			i+=2;
			res += 1;
		}
		else
		{
			*res = nul[i];
			res += 1;
		}
	}
	return bis;
}

void work_lzw(char *input, char *filename)
{

	asprintf(&filename,"%s%s","../fichiers_utilisateur/",filename);
	struct dictionary *ret = build();
	struct dictionary *c = ret;
	struct dictionary *e = ret;
	struct dictionary *d = build();

	char *user = calloc(1,strlen(input)*sizeof(char));
	user = to_ascii(input);
	printf("chaine = %s\n",user);
	char *try = calloc(1,500*sizeof(char));
	
	char *tty = calloc(1,500*sizeof(char));
	int *tab2 = calloc(10000,sizeof(int));
	int *balec = malloc(5000*sizeof(int));
	tty=final(ret,user,tab2,balec);

	printf("\n");
	size_t v = 0;
	while(c!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s\n",v,c->value);// numeric value : %i \n",v,c->value, c->num);
		c = c->next;
		v += 1;
	}
	//free(c);
	printf("\nPhrase initiale : %s\n\n",to_ascii(input));
	printf("Nombre de caracteres : %li\n",strlen(input));

	printf("Resultat apres compression : %s -----> ",tty);//(final(d,argv[1],n,balec)));
	int saude = sod(d);
	//printf("saud = %i\n",saude);
	int saud = sod(e);
	//int pr = *balec*nec(saud);
	//printf("pr = %i\n",pr);
	//printab(n);
	//printf("%i * %i = %i bits\n\n",*balec,nec(saud),pr);
	/*printf("ce tab : %i\n",*n);
	n += 1;
	printf("ce tab : %i\n",*n);*/
	//printab(n);
	
		///////////////:ICIIIIIIIIIIIIII
	int which = -1;
	int *rep = calloc(1,10000*sizeof(int));
	if(saud < 256)
	{
		struct double_tab *prisoner = build_huit(tab2,*balec,filename);
		(void)prisoner;
		which = 8;
		//printf("on est sur 8 bits\n");
		

	}
	else if(saud < 512)
	{
		struct double_tab *prisoner = build_neuf(tab2,*balec,filename);
		(void)prisoner;
		which = 9;
		//printf("on est sur 9 bits\n");
		
	}
	else if(saud < 1023)
	{
		struct double_tab *prisoner = build_dix(tab2,*balec,filename);
		(void)prisoner;
		which = 10;
		//printf("on est sur 10 bits\n");
		
	}
	else if(saud < 2048)
	{
		struct double_tab *prisoner = build_onze(tab2,*balec,filename);
		(void)prisoner;
		which = 11;
		//printf("on est sur 11 bits\n");
		
	}
	else 
	{
		struct double_tab *prisoner = build_douze(tab2,*balec,filename);
		(void)prisoner;
		which = 12;
		//printf("on est sur 12 bits\n");
		
	}
	printf("on travail sur %i bits\n",which);

	char *bin1 = calloc(1,10*sizeof(char));
	asprintf(&bin1,"%s.bin1",filename);
	char *bin2 = calloc(1,10*sizeof(char));
	asprintf(&bin2,"%s.bin2",filename);

	long somme = size(bin1)+size(bin2);
	printf("LA TAILLE DU FICHIER TEST EST DE : %li\n",size(bin1));
	printf("LA TAILLE DU FICHIER TESTB EST DE : %li\n",size(bin2));
	printf("La somme totale de l'enregistrement est de : %li octets\n",size(bin1)+size(bin2));
	(void)somme;
	(void)saude;
	(void)try;
	(void)rep;


	/*size_t v = 0;
	while(c!=NULL)
	{
		//printf("pipi\n");
		printf("Dic[%zu] = %s, numeric value : %i \n",v,c->value, c->num);
		c = c->next;
		v += 1;
	}*/
	
}

//~ int main(int argc, char *argv[])
//~ {
	//~ if(argc != 2)
		//~ errx(1,"2 arguments excpected");
	
	//~ work_lzw(argv[1]);
//~ }

double abss(double d)
{
	if(d > 0)
		return d;
	return -d;
}
char *retour_lzw(char *filename)
{

	char *try = calloc(1,500*sizeof(char));
	char *bin1 = calloc(1,10*sizeof(char));
	asprintf(&bin1,"%s.bin1",filename);
	char *bin2 = calloc(1,10*sizeof(char));
	asprintf(&bin2,"%s.bin2",filename);
	
	//int saude = sod(d);
	//printf("saud = %i\n",saude);
	//int saud = sod(e);
	//int pr = *balec*nec(saud);
	//printf("pr = %i\n",pr);
	//printab(n);
	//printf("%i * %i = %i bits\n\n",*balec,nec(saud),pr);
	/*printf("ce tab : %i\n",*n);
	n += 1;
	printf("ce tab : %i\n",*n);*/
	//printab(n);
	printf("what the hell\n");
		///////////////:ICIIIIIIIIIIIIII
	int which = -1;
	int *rep = calloc(1,10000*sizeof(int));
	if(size(bin2) == 0)
	{
		which = 8;
		//printf("on est sur 8 bits\n");
		rep = recup8(bin1,bin2);
		int a = 0;
		while(*rep != -1)
		{
			a+=1;
			//printf("rep %i\n",*rep);
			rep += 1;
		}
		*rep = -1;
		rep -= a + 1;

	}
	else if((double)(size(bin1) / size(bin2)) > 4)
	{
		which = 9;
		printf("on est sur 9 bits\n");
		rep = recup9(bin1,bin2);
	}
	else if(abss(4 - (double)((size(bin1) / size(bin2))) < 0.1))
	{
		which = 10;
		printf("on est sur 10 bits\n");
		rep = recup10(bin1,bin2);
	}
	else if(abss(2 - (double)((size(bin1) / size(bin2))) < 0.1))
	{
		which = 12;
		//printf("on est sur 11 bits\n");
		rep = recup12(bin1,bin2);
	}
	else 
	{
		which = 11;
		//printf("on est sur 12 bits\n");
		rep = recup11(bin1,bin2);
	}
	printf("on travail sur %i bits\n",which);
		////////////////LAAAAAAAAAAAAAAAAA

	//struct double_tab *prisoner = build_neuf(tab2,*balec);
	//int *ress = recup9("test.bin","testb.bin");

	long somme = size(bin1)+size(bin2);
	printf("LA TAILLE DU FICHIER TEST EST DE : %li\n",size(bin1));
	printf("LA TAILLE DU FICHIER TESTB EST DE : %li\n",size(bin2));
	printf("La somme totale de l'enregistrement est de : %li octets\n",size(bin1)+size(bin2));

	char *rett = inch(rep,try);
	printf("Resultat apres decompression : %s\n",rett);
	//int apr = strlen(input);
	//printf("%li * %i = %i octets\n\n",strlen(input),8,apr);
	//printf("nbword = %i\n",nbword(tty));
	//printf("Taux de compression : %.2f%%\n\n",100 - (double)somme/(double)apr*100);

	//(void)saude;
	(void)try;
	(void)somme;
	//(void)try;
	return rett;
}




