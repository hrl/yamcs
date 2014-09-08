#ifndef	__FUNCTIONS_H
#define __FUNCTIONS_H 1
#include <gtk/gtk.h>
#include "structs.h"

/* Builder Function */
/* Helper function */
void error_out(char *error);
void clean_var();
void call_last_func();
void build_UI();

GtkWidget **create_message_dialog(GtkWindow *fwindow, char *messages, GtkMessageType type, GtkWidget **dialog_response);
GtkWidget **create_edit_dialog(GtkWindow *fwindow, int rws, char argi[][100], GtkWidget **dialog_response);

int category_create(Category **head ,char code, char name[], int clothes_count, Clothes *clothes);
int clothes_create(Clothes **head, char name[], char type, float price, int order_count, float mark, Category *category, Order *order);
int order_create(Order **head, char date[], char name[], int mark, Clothes *clothes);
int customer_create(Customer **head, char name[], int clothes_count, float money_count, float mark);

int data_delete();
int category_delete(void *self);
int clothes_delete(void *self);
int order_delete(void *self);
int customer_delete(void *self);

Category **category_search(char code);
Clothes **clothes_search(char name[30]);
Customer **customer_search(Customer **head, char name[20]);

void data_out();

void create_list_store(GtkListStore **liststore, int type);
void insert_into_list_store(GtkListStore **liststore, void *data, int type);
void append_column(char column_title[][20], int column_line[], int cls);
void create_column(int type);
void clean_column();
char *string(char code);
char *ctype_to_string(char type);
char string_to_ctype(char *str);

/* End Helper function */

/* Basic I/O */
int save_file();
void open_file(char *filename);
int load_file();
void close_file(); /* clean data then you can change file */
char *file_choose(int type);

void file_new();
void file_open();
void file_save();
void file_save_as();
void file_quit();
/* End Basic I/O */

/* Maintenance */
int maintenance_category_dialog(void *self);

void maintenance_add_category();
void maintenance_add_clothes();
void maintenance_add_order();

void maintenance_edit();
void maintenance_delete();
/* End Maintenance */

/* Query */
void query_category_all(void *pass, int call_type);
void query_clothes_all(void *pass, int call_type);
void query_order_all(void *pass, int call_type);
void query_category_code(void *pass, int call_type);
void query_clothes_name(void *pass, int call_type);
void query_clothes_code_price(void *pass, int call_type);
void query_order_customer_date(void *pass, int call_type);
void query_order_name_mark(void *pass, int call_type);
/* End Query */

/* Statistics */
void statistics_category(void *pass, int call_type);
void statistics_year(void *pass, int call_type);
void statistics_customer(void *pass, int call_type);
void statistics_quarter(void *pass, int call_type);
void statistics_all(void *pass, int call_type);
/* End Statistics */

/* Other Function */
void other_about();
/* End Other Function */

#endif /* functions.h */