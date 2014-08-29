#ifndef	__STRUCTS_H
#define __STRUCTS_H 1

struct container
{
	void **data;
	struct container *next;
};

typedef struct container Container;

struct category
{
	char code;
	char name[10];
	int clothes_count;
	struct category *next;
	struct clothes *clothes;
	int (*__delete)(Container **self);
	int (*__edit)(Container **self, void *data);
};

struct clothes
{
	char name[30];
	char type;
	float price;
	int order_count;
	float mark;
	struct clothes *next;
	struct category *category;
	struct order *order;
	int (*__delete)(Container **self);
	int (*__edit)(Container **self, void *data);
};

struct order
{
	char date[10];
	char name[20];
	int mark;
	struct order *next;
	struct clothes *clothes;
	struct category *category;
	int (*__delete)(Container **self);
	int (*__edit)(Container **self, void *data);
};

typedef struct category Category;
typedef struct clothes Clothes;
typedef struct order Order;

#endif /* struct.h */