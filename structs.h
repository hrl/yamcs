#ifndef	__STRUCTS_H
#define __STRUCTS_H 1

/* --------------------------------------------------------------------------------- */
/* There are two main structs in this program: */
/* 1.Container */
/* 2.Category, Clothes, or Order */
/* The second struct are used to convert data between mem and disk. */
/* The first struct are used to storage the **unique** pointer of the second struct, */
/* and then we can use it to  */
/* --------------------------------------------------------------------------------- */

/* data: Category **, Clothes **, or Order **. */
/* these pointer are unique */
struct container
{
	void *data;
	struct container *next;
};

typedef struct container Container;

/* function __delete and __edit are called through the Container that contains */
/* the pointer of the pointer of this struct */
/* self is the pointer of the pointer of this struct */
struct category
{
	char code;
	char name[10];
	int clothes_count;
	struct category *next;
	struct clothes *clothes;
	int (*__delete)(void *self);
	int (*__edit)(void *self, void *data);
	//int (*__delete)(Container **self, int type);
	//int (*__edit)(Container **self, void *data);
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
	int (*__delete)(void *self);
	int (*__edit)(void *self, void *data, ...);
	//int (*__delete)(Container **self, int type);
	//int (*__edit)(Container **self, void *data);
};

struct order
{
	char date[10];
	char name[20];
	int mark;
	struct order *next;
	struct clothes *clothes;
	struct category *category;
	int (*__delete)(void *self);
	int (*__edit)(void *self, void *data, ...);
	//int (*__delete)(Container **self, int type);
	//int (*__edit)(Container **self, void *data);
};

typedef struct category Category;
typedef struct clothes Clothes;
typedef struct order Order;

#endif /* struct.h */