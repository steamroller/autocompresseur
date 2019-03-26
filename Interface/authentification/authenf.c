#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>



GtkBuilder* builder;

/* BUTTON*/

GtkWidget* new_user;
GtkWidget* new_file_button;
GtkWidget* open_file_button;
GtkWidget* setting_button;
GtkWidget* save_button;
GtkWidget* close_edit_button;

/*CONNECT*/


GtkLabel* textlabel;

GtkEntry* name_entry;
GtkEntry * password_entry;
GtkLabel * connexion_message;


const gchar * name;
const gchar * password;

/* WINDOW */

GtkWidget * main_window;
GtkWidget * menu_window;
GtkWidget * settings_window;
GtkWidget * edit_window;

	

int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);


	builder=gtk_builder_new();

	//------ GET ELEMENT FROM GLADE FILE
	gtk_builder_add_from_file(builder,"autocompresseur_gui.glade",NULL);
	
	main_window=GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
	menu_window=GTK_WIDGET(gtk_builder_get_object(builder,"menu_window"));
	settings_window=GTK_WIDGET(gtk_builder_get_object(builder,"settings_window"));
	edit_window=GTK_WIDGET(gtk_builder_get_object(builder,"edit_window"));


	new_user=GTK_WIDGET(gtk_builder_get_object(builder,"new_user_button"));
	new_file_button=GTK_WIDGET(gtk_builder_get_object(builder,"new_file_button"));
	open_file_button=GTK_WIDGET(gtk_builder_get_object(builder,"open_file_button"));
	setting_button=GTK_WIDGET(gtk_builder_get_object(builder,"setting_button"));
	save_button=GTK_WIDGET(gtk_builder_get_object(builder,"new_user_button"));
	close_edit_button=GTK_WIDGET(gtk_builder_get_object(builder,"close_edit_button"));

	connexion_message= GTK_LABEL(gtk_builder_get_object(builder,"connexion_message"));
	name_entry=GTK_ENTRY(gtk_builder_get_object(builder,"login_entry"));
	password_entry=GTK_ENTRY(gtk_builder_get_object(builder,"password_entry"));

	//------ CONNECT BUTTON
	gtk_builder_connect_signals(builder,NULL);
	g_object_unref(builder);
	gtk_widget_show(main_window);
	gtk_main();
	return  0;


}

char* strncpy(char *dest, const char *src,size_t n){
    size_t i;

    for (i = 0 ; i<n && src[i] != '\0' ; i++)
        dest[i] = src[i];
    for ( ; i < n ; i++)
        dest[i] = '\0';

    return dest;
}

//--- COMPAR ENTRY DATA AND FILE DATA
int compar(	char* rdname,const gchar* s2,size_t len_rd,size_t len_enter)
{
	char *cmp=rdname;
	
	size_t c=0;
	if(len_rd != len_enter)
		return 1;
	while(c<len_rd && c<len_enter)
	{
		if(cmp[c]!=s2[c])
		{
			return 1;
		}
		
		c++;
	}
	
	return 0;
}

//---- CREATE AN ACCOUNT (FILES)
void on_new_user_button_clicked()
{
	name= gtk_entry_get_text(GTK_ENTRY(name_entry));
	password= gtk_entry_get_text(GTK_ENTRY(password_entry));
	
	size_t len_login=strlen(name);
	size_t len_password=strlen(password);
	char nam[len_login];

	char  pass[len_password];
	strncpy(nam,name,len_login);
	strncpy(pass,password,len_password);
	if(access("userdatal",R_OK)!=-1)
		gtk_label_set_text(GTK_LABEL(connexion_message),"There is already an account on this computer ! ");
	else
	{
		printf("------------------New account------------------\n");
		printf("Login: %s \nPassword: %s \n\n", name, password);

		int fdl=open("userdatal",O_TRUNC|O_CREAT|O_RDWR,00700);
		int fdm=open("userdatam",O_TRUNC|O_CREAT|O_RDWR,00700);
		write(fdl,nam,len_login);
		write(fdm,pass,len_password);
		gtk_label_set_text(GTK_LABEL(connexion_message),"Account created !");
	}

}

//---- CONNEXION USING THE COMPAR FUNCTION
void on_connexion_button_clicked()
{
	name= gtk_entry_get_text(GTK_ENTRY(name_entry));
	password= gtk_entry_get_text(GTK_ENTRY(password_entry));
	size_t len_enter_name=strlen(name);
	size_t len_enter_password=strlen(password);
	

	int fdl=open("userdatal",O_RDWR,00700);
	int fdm=open("userdatam",O_RDWR,00700);
	if(fdm ==-1 || fdl==-1)
		gtk_label_set_text(GTK_LABEL(connexion_message),"You should create an account");
	else
	{
		printf("------------------Connexion------------------\n");
		printf("Name entry : %s \nPassword entry: %s \n", name, password);


		char rdname[len_enter_name];
		rdname[len_enter_name-1]='\n';
		char rdpassword[len_enter_password];
		rdname[len_enter_password-1]='\n';
		size_t len_rd_name=read(fdl,rdname,20);
		size_t len_rd_password=read(fdm,rdpassword,20);
	
		int cmn=compar(rdname,name,len_rd_name,len_enter_name);
		
		int cmp=compar(rdpassword,password,len_rd_password,len_enter_password);
		printf("\n\n\n");
		if(cmp==0 && cmn==0)
		{
			printf("        Connected  !            \n");
			gtk_label_set_text(GTK_LABEL(connexion_message),"Connected !");
			gtk_widget_show(menu_window);
			gtk_widget_hide(main_window);
	
		}
		else
		{
			printf("Wrong login or password, try again.\n");
			gtk_label_set_text(GTK_LABEL(connexion_message),"Wrong login or password, try again.");
			
		}
	
	}
}


void on_new_file_button_clicked()
{
	gtk_widget_show(edit_window);
	gtk_widget_hide(menu_window);

}

void on_open_file_button_clicked()
{


}


void on_setting_button_clicked()
{
	gtk_widget_show(settings_window);
	gtk_widget_hide(menu_window);

}


void on_close_edit_button_clicked()
{
	gtk_widget_show(menu_window);
	gtk_widget_hide(edit_window);
}


void on_save_button_clicked()
{

}

void on_apply_button_clicked()
{
	gtk_widget_show(menu_window);
	gtk_widget_hide(settings_window);
}
