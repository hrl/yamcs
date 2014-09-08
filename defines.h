#ifndef	__DEFINES_H
#define __DEFINES_H 1

#define UI_FILE "UI.xml"

const char *version = "0.1";
const char *program_name = "Yet Another Manager of a simple Clothing Shop";
const char *comments = "Full of Bugs.\nIt Works.";
const char *author[] = {"Ruilin Huang", NULL};

FILE *file = NULL;
short updated; /*  */
GtkWindow *window = NULL;
GtkTreeView *treeview = NULL;
void (*last_func)(void *pass, int call_type);

Category *category_head;  /* Main head of the linked list */

Container *category_list_head = NULL;
Container *clothes_list_head = NULL;
Container *order_list_head = NULL;

enum {
	FILE_CHOOSE_OPEN,
	FILE_CHOOSE_SAVE,
	FILE_CHOOSE_SAVE_AS,
};

enum {
	TYPE_CATEGORY,
	TYPE_CLOTHES,
	TYPE_ORDER,
};

enum {
	CATEGORY_ALL_POINTER,
	CATEGORY_ALL_TYPE,
	CATEGORY_ALL_CODE,
	CATEGORY_ALL_NAME,
	CATEGORY_ALL_CLOTHES_COUNT,
	CATEGORY_ALL_COLUMNS
};

enum {
	CLOTHES_ALL_POINTER,
	CLOTHES_ALL_TYPE,
	CLOTHES_ALL_CODE,
	CLOTHES_ALL_NAME,
	CLOTHES_ALL_CTYPE,
	CLOTHES_ALL_PRICE,
	CLOTHES_ALL_MARK,
	CLOTHES_ALL_ORDER_COUNT,
	CLOTHES_ALL_COLUMNS
};

enum {
	ORDER_ALL_POINTER,
	ORDER_ALL_TYPE,
	ORDER_ALL_CNAME,
	ORDER_ALL_DATE,
	ORDER_ALL_NAME,
	ORDER_ALL_MARK,
	ORDER_ALL_COLUMNS
};

enum {
	CALL_TYPE_NORMAL,
	CALL_TYPE_REDO,
};

#endif /* defines.h */