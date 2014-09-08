#ifndef	__DEFINES_H
#define __DEFINES_H 1

#define UI_FILE "UI.xml"

const char *version = "0.2";
const char *program_name = "Yet Another Manager of a simple Clothing Shop";
const char *comments = "Full of Bugs.\nIt Works.";
const char *website = "https://github.com/hrl/yamcs";
const char *website_lable = "GitHub";
const char *author[] = {"Ruilin Huang", NULL};

FILE *file = NULL;
short updated = TRUE;
GtkWindow *window = NULL;
GtkTreeView *treeview = NULL;
void (*last_func)(void *pass, int call_type);

Category *category_head;  /* Main head of the linked list */

enum {
	FILE_CHOOSE_OPEN,
	FILE_CHOOSE_SAVE,
	FILE_CHOOSE_SAVE_AS,
};

enum {
	TYPE_CATEGORY,
	TYPE_CLOTHES,
	TYPE_ORDER,
	TYPE_OTHER
};

enum {
	CATEGORY_ALL,
	CLOTHES_ALL,
	ORDER_ALL,
	CATEGORY_STATS,
	CLOTHES_YEAR,
	CUSTOMER_STATS,
	ALL_STATS
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
	CATEGORY_STATS_POINTER,
	CATEGORY_STATS_TYPE,
	CATEGORY_STATS_CODE,
	CATEGORY_STATS_NAME,
	CATEGORY_STATS_ORDER_COUNT,
	CATEGORY_STATS_SALES_COUNT,
	CATEGORY_STATS_MARKL3_COUNT,
	CATEGORY_STATS_MARKG3_COUNT,
	CATEGORY_STATS_COLUMNS
};

enum {
	CLOTHES_YEAR_POINTER,
	CLOTHES_YEAR_TYPE,
	CLOTHES_YEAR_NAME,
	CLOTHES_YEAR_CNAME,
	CLOTHES_YEAR_ORDER_COUNT,
	CLOTHES_YEAR_SALES_COUNT,
	CLOTHES_YEAR_MARK,
	CLOTHES_YEAR_COLUMNS
};

enum {
	CUSTOMER_STATS_POINTER,
	CUSTOMER_STATS_TYPE,
	CUSTOMER_STATS_NAME,
	CUSTOMER_STATS_ORDER_COUNT,
	CUSTOMER_STATS_MONEY_COUNT,
	CUSTOMER_STATS_MARK,
	CUSTOMER_STATS_COLUMNS
};

enum {
	QUARTER_STATS_POINTER,
	QUARTER_STATS_TYPE,
	QUARTER_STATS_NAME,
	QUARTER_STATS_C1_COUNT,
	QUARTER_STATS_C2_COUNT,
	QUARTER_STATS_C3_COUNT,
	QUARTER_STATS_C4_COUNT,
	QUARTER_STATS_C5_COUNT,
	QUARTER_STATS_COLUMNS
};

enum {
	ALL_STATS_POINTER,
	ALL_STATS_TYPE,
	ALL_STATS_ORDER_COUNT,
	ALL_STATS_SALES_COUNT,
	ALL_STATS_MARKL3_COUNT,
	ALL_STATS_MARKG3_COUNT,
	ALL_STATS_COLUMNS
};

enum {
	CALL_TYPE_NORMAL,
	CALL_TYPE_REDO,
};

#endif /* defines.h */