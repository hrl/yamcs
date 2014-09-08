#ifndef	__STRUCTS_H
#define __STRUCTS_H 1

struct category
{
	int (*__delete)(void *self);
	char code;
	char name[10];
	int clothes_count;
	struct category *next;
	struct clothes *clothes;
};

struct clothes
{
	int (*__delete)(void *self);
	char type;
	char name[30];
	int order_count;
	float price;
	float mark;
	struct clothes *next;
	struct category *category;
	struct order *order;
};

struct order
{
	int (*__delete)(void *self);
	char date[10];
	char name[20];
	int mark;
	struct order *next;
	struct clothes *clothes;
};

struct customer
{
	char name[20];
	int order_count;
	float money_count;
	float mark;
	struct customer *next;
};

typedef struct category Category;
typedef struct clothes Clothes;
typedef struct order Order;
typedef struct customer Customer;

struct call_func
{
	int (*__delete)(void *self);
};

typedef struct call_func Call_func;

#endif /* struct.h */