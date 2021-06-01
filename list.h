#include<stdio.h>
#include<stdlib.h>
typedef struct data
{
	char ch;
	struct data *next;
}data;
typedef struct list
{
	data *head, *tail;
}list;
void init(list *l);
void enlist(list *l, char ch);
void remov(list *l, char ch);
int searchlist(list *l, char ch);
int isempty(list *l);
int charsearch(list *l, char ch);
int length(list *l);
void printlist(list *l);
