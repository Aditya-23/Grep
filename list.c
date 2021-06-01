#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include<string.h>
void init(list *l)
{
	l->head = l->tail = NULL;
}

void enlist(list *l, char ch)
{
	data *tmp;
	tmp = (data *)malloc(sizeof(data));
	tmp->ch = ch;
	tmp->next = NULL;
	if(l->head == NULL)
	{
		l->head = l->tail = tmp;
		return;
	}
	l->tail->next = tmp;
	l->tail = l->tail->next;
	return;
}

void remov(list *l, char ch)
{
	char c;
	data *tmp, *p, *q = NULL;
	p = l->head;
	while(p != NULL)
	{
	  	if(p->ch == ch)
		{
			c = p->ch;
			tmp = p;
			if(p == l->head)
			{
				l->head = l->head->next;
				free(tmp);
				return;
			}
			else if(p == l->tail)
			{
				l->tail = q;
				l->tail->next = p->next;
				free(tmp);
				return;
			}
			else
			{
				q->next = p->next;
				free(tmp);
				return;
			}	
		}
		q = p;
		p = p->next;
	}
}

int searchlist(list *l, char ch)
{
	data *p, *q = NULL, *tmp;
	p = l->head;
	while(p != NULL)
	{
		if(p->ch == ch)
		{
			tmp = p;
			if(p == l->head)
			{
				l->head = l->head->next;
			}
			else
			{
				q->next = p->next;
			}
			free(tmp);
			return 1;	
		}
		q = p;
		p = p->next;
	}
	return 0;
}
int isempty(list *l)
{
	if(l->head == NULL)
		return 1;
	else
		return 0;
}
int charsearch(list *l, char ch)
{
	data *p;
	p = l->head;
	while(p != NULL)
	{
		if(p->ch == ch)
			return 1;
		p = p->next;
	}
	return 0;
}
int length(list *l)
{
	data *p;
	int count = 0;
	p = l->head;
	while(p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}
void printlist(list *l)
{
	data *p;
	p = l->head;
	while(p != NULL)
	{
		printf("%c", p->ch);
		p = p->next;
	}
}










































	





































			













		
		
