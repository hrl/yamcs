#ifndef	__FUNCTIONS_H
#define __FUNCTIONS_H 1
#include <gtk/gtk.h>
#include "structs.h"

/* Builder Function */
/* Helper function */
void error_out(char *error);
void build_UI();
void insert_into_container(Container **head, void *data);
int category_delete(Category *self);
int category_edit(Category *self, int argc, void *argv[]);
int clothes_delete(struct clothes *self);
int clothes_edit(struct clothes *self, int argc, void *argv[]);
int order_delete(struct order *self);
int order_edit(struct order *self, int argc, void *argv[]);
/* End Helper function */

/* Basic I/O */
short save_file();
void open_file(char *filename);
short load_file();
void close_file(); /* clean data then you can change file */
char *file_choose(int type);

void file_new();
void file_open();
void file_save();
void file_save_as();
void file_quit();
/* End Basic I/O */

/* Maintenance */

/* End Maintenance */

/* Query */
/* End Query */

/* Statistics */
/* End Statistics */

/* Other Function */
void other_about();
/* End Other Function */

#endif /* functions.h */