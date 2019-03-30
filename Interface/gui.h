#ifndef GUI_H
#define GUI_H

/*
GtkBuilder* builder=NULL;
gtk_builder_add_from_file(builder,"autocompresseur_gui.glade",NULL);
GtkWidget *main_window=GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
*/
typedef struct
{
	GtkBuilder *builder;
	gpointer user_data;

} SGlobalData;

struct main_board
{
	struct user* next; 
	size_t size;
};

struct user
{
	char* name;
	char* password;
	size_t nb_file;
	struct file_board* file;
};

struct file_board
{
	char* pathname;
	struct file_board* next; 
};

struct main_board* main_board_init();
struct user* user_init();
struct file_board* file_board_init();

int  add_user( struct main_board *main_board, char* name, char* password);
int is_name_available(struct main_board* main_board, char* name);
int connexion(struct main_board* main_board, char* name, char* password);

#endif
