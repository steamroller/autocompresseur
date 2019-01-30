#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>

#include "hautenf.h"
/*
void init()
{

SGlobalData data;
(data).builder=Gtk_new_builder();
gtk_builder_add_from_file(data.builder,"autocompresseur_gui.glade",NULL);
GtkWidget* main_window=GTK_WIDGET(gtk_builder_get_object(data.builder,"main_window"));
GtkLabel* connexion_message= GTK_WIDGET(gtk_builder_get_object(data.builder,"connexion_message"));
GtkWidget* name_entry=GTK_WIDGET(gtk_builder_get_object(data.builder,"login_entry"));
GtkWidget* password_entry=GTK_WIDGET(gtk_builder_get_object(data.builder,"password_entry"));

}
*/




void print(struct user* user)
{
	struct user* tmp = user;
	if( tmp!=NULL)
	{
		struct file_board * tmp =user->file;
		printf(" %s :", user->name);
    
		
		while(tmp!=NULL)
		{
			char * s= tmp->pathname;
			printf(" %s | ", s);	
			tmp=tmp->next;
		}
	}
	printf("NULL \n");
	
}



//-----------------------------INIT------------------------------------

struct main_board* main_board_init()
{
	struct main_board* new_board= calloc(4, sizeof(struct main_board));
	if(new_board==NULL)
		 errx(1,"main_board init failed");
	return new_board;
}


struct user* user_init()
{
	struct user* new_user = calloc(10,sizeof(struct user));
	if(new_user==NULL)
		errx(1,"user init failed");
	return new_user;
}


struct file_board* file_board_init()
{
	struct file_board* new_file_board=calloc(1,sizeof(struct file_board));
	if(new_file_board==NULL)
		errx(1,"file_board init failed ");
	return new_file_board;
}
//-------------------------OPERATIONS----------------------------------


int  add_user( struct main_board* main_board, char* name, char* password)
{
	struct user* new_user=user_init();
	new_user->name=name;
	new_user->password=password;
	(main_board + main_board->size)->next=new_user;
	(main_board->size)+=1;
	return 1;
}

int connexion(struct main_board* main_board, char* name, char* password)
{
	size_t i =main_board->size;
	for(size_t j=0;j<i && (main_board +j)!=NULL && (main_board +j)->next!=NULL ;j++)
	{
				
		if((main_board+j)->next!=NULL && (main_board+j)->next->name == name && (main_board+j)->next->password == password ) 
			return 1;
	}

	return 0;
}

void add_file(struct user * user, char* pathname)
{
	
	struct file_board* new_file=file_board_init();
	new_file->pathname=pathname;
	size_t i = user->nb_file;
	struct file_board* tmp=user->file;

	if(i ==0)
		user->file=new_file;
	else
	{
		while(tmp->next !=NULL)
			tmp=tmp->next;
		tmp->next=new_file;
	}	
	(user->nb_file)+=1;
}

int compar(char* s1,const gchar* s2)
{
//	char* cmp=s1;
	int c=0;
	c=c;
	s1=s1;
	s2=s2;
	/*
	while(*cmp)
	{
		if(*cmp!=s2[c])
			return 1;
		cmp++;
		c++;
	}*/
	return 0;
}
/*
void connexion()
{
	
	printf("-------------------- WELCOME IN AUTOCOMPRESSION------------------\n\n\n");

	printf("Please select a choice \n\n");
	printf("1. Connexion   2. New user \n\n");
	int choice;
	scanf("%d",&choice);


	if(choice==2)
	{
		char name[4];
		char password[4];
		printf("name : ");
		scanf("%s",&name);
		printf("\n");
		printf("password : ");
		scanf("%s",&password);

		int fd =open("userdata",O_RDWR|O_CREAT);
		if(fd==-1)
			errx(1,"create userdata failed");
		write(fd,name,4);
		write(fd,"\n",1);
		write(fd,password,4);
		write(fd,"\n",1);
		printf( " ACCOUNT CREATED ! \n\n\n");
	}
	else
	{
		int connected=1;
		while(connected ==1)
		{
			char name[4];
			char password[4];
			printf("name : ");
			scanf("%s",&name);
			printf("\n");
			printf("password : ");
			scanf("%s",&password);



			FILE *userdata=fopen("userdata","r");
			char *rdname=NULL;
			char *rdpassword=NULL;
			size_t len=0;

			getline(&rdname,&len,userdata);
			getline(&rdpassword,&len,userdata);
			rdname[4]=0;
			rdpassword[4]=0;
			int cmn=compar(rdname,name);
			int cmp=compar(rdpassword,password);
			if ( cmn==0 && cmp==0)
			{
				connected =0;
				printf("CONNECTED \n");
			}
			else
				printf(" Wrong login or password, try again \n");
		}

	}

}*/
/*
int connect(GtkButton* button)
{
	char name[4];
	char password[4];

	(void)button;

	const gchar* name= gtk_entry_get_text(GTK_ENTRY(name_entry));
	const gchar* password= gtk_entry_get_text(GTK_ENTRY(password_entry));
	FILE *userdata=fopen("userdata","r");

	char *rdname=NULL;
	char *rdpassword=NULL;
	size_t len=0;

	fgets(rdname,len,userdata);
	fgets(rdpassword,len,userdata);
	rdname[4]=0;
	rdpassword[4]=0;
	int cmn=compar(rdname,name);
	int cmp=compar(rdpassword,password);
	if(cmp==cmn)
	{
		
		return 0;
	}
	else
	{
		gtk_label_set_text(GTK_LABEL(connexion_message),"Wrong login or password, try again.");
		return 1;
	}
}
*/
/*
int connect(GtkButton* button)
{
	(void)button;	
	const gchar* text="YOOOOO";
	GtkLabel* textlabel=GTK_LABEL(gtk_builder_get_object(data.builder,"connexion_message"));
	if(textlabel==NULL)
		errx(1,"textlabel not find :/ ");
	gtk_label_set_text(textlabel,text);
	return 1;
}*/

	

int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);
	
	GtkWidget * main_window;

 	SGlobalData data;
	data.builder=gtk_builder_new();
	gtk_builder_add_from_file(data.builder,"autocompresseur_gui.glade",NULL);
	GtkWidget* connexion_message= GTK_WIDGET(gtk_builder_get_object(data.builder,"connexion_message"));

	main_window=GTK_WIDGET(gtk_builder_get_object(data.builder,"main_window"));
	if(main_window==NULL)
		fprintf(stderr,"unable to find object with id \"main_window\" \n");
	gtk_builder_connect_signals(data.builder,&data);
	gtk_widget_show(main_window);
	const gchar* text="test message d'erreur";
	gtk_label_set_text(GTK_LABEL(connexion_message),text);


	gtk_main();
	return 0;


}
