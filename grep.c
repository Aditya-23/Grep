#include<stdio.h>
#include<string.h>
#include<getopt.h>
#include<stdlib.h>
#include<limits.h>
#include<ctype.h>
#include<dirent.h>
#include "list.h"
void search(FILE *fp, char *str, list *s, char *filename, int m);
void isearch(FILE *fp, char *str, list *s, char *filename, int m);
char *iconvert(char *line, char *cline);
char *wordcompare(char *line, char *str);
void wsearch(FILE *fp, char *str, list *s, char *filename, int m);
void iwsearch(FILE *fp, char *str, list *s, char *filename, int m);
void print(char *line);
int number(char *c);
void recursive(char *location, char *string, list *s, int max);
int main(int argc, char *argv[])
{
	int c, i = 0, n, r, flag = 0, j, count = 0, fflag = 0;
	char str[300], string[1000], *file, *max, *loc, arr[20][100], reg_file[20][20];
	FILE *fp, *f1;
	extern char *optarg;
	extern int optind;
	list store;
	init(&store);
	while(i < argc)
	{
		strcpy(arr[i], argv[i]);
		i++;
	}
	while((c = getopt(argc, argv, "ivHhcqbm:f:wr")) != -1)
	{
		if(c == 'i' && !charsearch(&store, 'i'))
			enlist(&store, 'i');
		else if(c == 'v' && !charsearch(&store, 'v'))
			enlist(&store, 'v');
		else if(c == 'H' && !charsearch(&store, 'H'))
			enlist(&store, 'H');
		else if(c == 'c' && !charsearch(&store, 'c'))
			enlist(&store, 'c');
		else if(c == 'q' && !charsearch(&store, 'q'))
			enlist(&store, 'q');
		else if(c == 'b' && !charsearch(&store, 'b'))
			enlist(&store, 'b');
		else if(c == 'm' && !charsearch(&store, 'm'))
		{
			max = optarg;
			enlist(&store, 'm');
		}			
		else if(c == 'f' && !charsearch(&store, 'f'))
		{
			file = optarg;
			enlist(&store, 'f');
		}
		else if(c == 'w' && !charsearch(&store, 'w'))
			enlist(&store, 'w');
		else if(c == 'h' && !charsearch(&store, 'h'))
			enlist(&store, 'h');
		else if(c == 'r' && !charsearch(&store, 'r'))
		{
			loc = optarg;
			enlist(&store, 'r');
		}
	}
	
	i = 1;
	while(i < argc - 1)
	{
		if(arr[i][0] != '-')
		{
			if(charsearch(&store, 'm') && !charsearch(&store, 'f'))
			{
				if(strcmp(arr[i], max) != 0)
				{
					strcpy(str, arr[i]);
					flag = 1;
					break;
				}
			}
			if(!charsearch(&store, 'm') && charsearch(&store, 'f'))
			{
				if(strcmp(arr[i], file) != 0)
				{
					strcpy(str, arr[i]);
					flag = 1;
					break;
				}
			}
			if(charsearch(&store, 'm') && charsearch(&store, 'f'))
			{
				if(strcmp(arr[i], file) != 0 && strcmp(arr[i], max) != 0)
				{
					strcpy(str, arr[i]);
					flag = 1;
					break;
				}
			}
			if(!charsearch(&store, 'm') && !charsearch(&store, 'f'))
			{
				strcpy(str, arr[i]);
				flag = 1;
				break;
			}
		}
		i++;
	}
	j = 0;
	i = argc - 1;
	while(i > 0)
	{
		if(arr[i][0] == '-' || !strcmp(arr[i], str))
			break;		
		if(charsearch(&store, 'm') && !charsearch(&store, 'f'))
		{
			if(strcmp(arr[i], max) != 0)
			{
				strcpy(reg_file[j], arr[i]);
				fflag = 1;
				count++;
			}
		}
		if(!charsearch(&store, 'm') && charsearch(&store, 'f'))
		{
			if(strcmp(arr[i], file) != 0)
			{
				strcpy(reg_file[j], arr[i]);
				fflag = 1;
				count++;
			}
		}
		if(charsearch(&store, 'm') && charsearch(&store, 'f'))
		{
			if(strcmp(arr[i], file) != 0 && strcmp(arr[i], max) != 0)
			{
				strcpy(reg_file[j], arr[i]);
				fflag = 1;
				count++;
			}
		}
		if(!charsearch(&store, 'm') && !charsearch(&store, 'f'))
		{
			strcpy(reg_file[j], arr[i]);
			fflag = 1;
			count++;
		}
		j++;
		i--;
	}
	if(count > 1)
		if(!charsearch(&store, 'H'))
			enlist(&store, 'H');
	if(flag == 0 && !charsearch(&store, 'f'))
	{
		printf("grep:No input string\n");
		exit(1);
	}
	j = 0;
	if(charsearch(&store, 'r'))
	{
		remov(&store, 'r');
		if(!charsearch(&store, 'H'))
			if(!charsearch(&store, 'h'))
				enlist(&store, 'H');
		if(charsearch(&store, 'f'))
		{
			remov(&store, 'f');
			fp = fopen(file, "r");
			if(!fp)
			{
				printf("grep:file could not be opened\n");
				exit(1);
			}
			if(charsearch(&store, 'm'))
			{
				while(j < count)
				{
					while(fgets(string, 1000, fp) != NULL)
					{
						n = strlen(string);
						string[n - 1] = 0;
						recursive(reg_file[j], string, &store, atoi(max));
						r = fseek(fp, 0, 0);
					}
					j++;
				}
				exit(1);
			}
			else
			{
				while(j < count)
				{
					while(fgets(string, 1000, fp) != NULL)
					{
						n = strlen(string);
						string[n - 1] = 0;
						recursive(reg_file[j], string, &store, INT_MAX);
						r = fseek(fp, 0, 0);
					}
					j++;
				}
				exit(1);
			}
		}
		if(charsearch(&store, 'm'))
			while(j < count)
			{
				recursive(reg_file[j], str, &store, atoi(max));
				j++;
			}
		else
			while(j < count)
			{
				recursive(reg_file[j], str, &store, INT_MAX);
				j++;
			}
	}
	else
	{
		if(charsearch(&store, 'f'))
		{
			remov(&store, 'f');
			fp = fopen(file, "r");
			if(fp == NULL)
			{
				printf("grep:Failed to open the file\n");
				exit(1);
			}
			if(charsearch(&store, 'w'))
			{
				remov(&store, 'w');
				if(charsearch(&store, 'm'))
				{
					remov(&store, 'm');
					if(charsearch(&store, 'i'))
					{
						remov(&store, 'i');
						while(j < count)
						{
							f1 = fopen(reg_file[j], "r");
							if(f1 == NULL)
								printf("grep:Failed to open the file\n");
							else
							{
								while(fgets(string, 1000, fp) != NULL)
								{
									n = strlen(string);
									string[n - 1] = 0;
									iwsearch(f1, string, &store, reg_file[j], atoi(max));
									r = fseek(f1, 0, 0);
								}
							}
							j++;
						}
					}
					else
					{
						while(j < count)
						{
							f1 = fopen(reg_file[j], "r");
							if(f1 == NULL)
								printf("grep:Failed to open the file\n");
							else
							{
								while(fgets(string, 1000, fp) != NULL)
								{
									n = strlen(string);
									string[n - 1] = 0;
									wsearch(f1, string, &store, reg_file[j], atoi(max));
									r = fseek(f1, 0, 0);
								}
							}
							j++;
						}
					}
				}
				else
				{
					if(charsearch(&store, 'i'))
					{
						remov(&store, 'i');
						while(j < count);
						{
							f1 = fopen(reg_file[j], "r");
							if(f1 == NULL)
								printf("grep:Failed to open the file\n");
							else
							{
								while(fgets(string, 1000, fp) != NULL)
								{
									n = strlen(string);
									string[n - 1] = 0;
									iwsearch(f1, string, &store, reg_file[j], INT_MAX);
									r = fseek(f1, 0, 0);
								}
							}
							j++;
						}
					}
					else
					{
						while(j < count)
						{
							f1 = fopen(reg_file[j], "r");	
							if(f1 == NULL)
								printf("grep:Failed to open the file\n");
							else
							{
								while(fgets(string, 1000, fp) != NULL)
								{
									n = strlen(string);
									string[n - 1] = 0;
									wsearch(f1, string, &store, reg_file[j], INT_MAX);
									r = fseek(f1, 0, 0);
								}
							}
							j++;
						}	
					}
				}
			}
			else
			{
				if(charsearch(&store, 'm'))
				{
					remov(&store, 'm');
					if(charsearch(&store, 'i'))
					{
						remov(&store, 'i');
						while(j < count)
						{
							f1 = fopen(reg_file[j], "r");
							if(f1 == NULL)
								printf("grep:Failed to open the file\n");
							else
							{
								while(fgets(string, 1000, fp) != NULL)
								{
									n = strlen(string);
									string[n - 1] = 0;
									isearch(f1, string, &store, reg_file[j], atoi(max));
									r = fseek(f1, 0, 0);
								}
							}
							j++;
						}
					}
					else
					{
						while(j < count)
						{
							f1 = fopen(reg_file[j], "r");	
							if(f1 == NULL)
								printf("grep:Failed to open the file\n");
							else
							{
								while(fgets(string, 1000, fp) != NULL)
								{
									n = strlen(string);
									string[n - 1] = 0;
									search(f1, string, &store, reg_file[j], atoi(max));
									r = fseek(f1, 0, 0);
								}
							}
							j++;
						}
					}	
				}
				else
				{
					if(charsearch(&store, 'i'))
					{
						remov(&store, 'i');
						while(j < count)
						{
							f1 = fopen(reg_file[j], "r");
							if(f1 == NULL)
								printf("grep:Failed to open the file\n");
							else
							{
								while(fgets(string, 1000, fp) != NULL)
								{
									n = strlen(string);
									string[n - 1] = 0;
									isearch(f1, string, &store, reg_file[j], INT_MAX);
									r = fseek(f1, 0, 0);
								}
							}
							j++;
						}
					}
					else
					{
						while(j < count)
						{
							f1 = fopen(reg_file[j], "r");	
							if(f1 == NULL)
								printf("grep:Failed to open the file\n");
							else
							{
								while(fgets(string, 1000, fp) != NULL)
								{
									n = strlen(string);
									string[n - 1] = 0;
									search(f1, string, &store, reg_file[j], INT_MAX);
									r = fseek(f1, 0, 0);
								}
							}
							j++;
						}
					}	
				}
			}
		}	
		else if(charsearch(&store, 'w'))
		{
			remov(&store, 'w');
			if(charsearch(&store, 'm'))
			{
				remov(&store, 'm');
				if(charsearch(&store, 'i'))
				{
					remov(&store, 'i');
					if(!number(max))
					{
						printf("grep:invalid max count\n");
						exit(1);
					}
					while(j < count)
					{
						fp = fopen(reg_file[j], "r");
						if(fp == NULL)
							printf("grep:Cannot open the file\n");	
						else
							iwsearch(fp, str, &store, reg_file[j], atoi(max));
						j++;
					}
				}
				else
				{					
					if(!number(max))
					{
						printf("grep:invalid max count\n");
						exit(1);
					}
					while(j < count)
					{
						fp = fopen(reg_file[j], "r");
						if(fp == NULL)
							printf("grep:Cannot open the file\n");		
						else
							wsearch(fp, str, &store, reg_file[j], atoi(max));
						j++;
					}
				}				
			}
			else
			{
				if(charsearch(&store, 'i'))
				{
					remov(&store, 'i');
					while(j < count)
					{
						fp = fopen(reg_file[j], "r");
						if(fp == NULL)
							printf("grep:Cannot open the file\n");	
						else
							iwsearch(fp, str, &store, reg_file[j], INT_MAX);
						j++;
					}
				}
				else
				{
					while(j < count)
					{
						fp = fopen(reg_file[j], "r");
						if(fp == NULL)
							printf("grep:Cannot open the file\n");		
						else
							wsearch(fp, str, &store, reg_file[j], INT_MAX);
						j++;
					}
				}
			}
		}
		else
		{
			if(charsearch(&store, 'm'))
			{
				remov(&store, 'm');
				if(charsearch(&store, 'i'))
				{
					remov(&store, 'i');	
					if(!number(max))
						printf("grep:invalid max count\n");	
					while(j < count)
					{
						fp = fopen(reg_file[j], "r");
						if(fp == NULL)
							printf("grep:Cannot open the file\n");
						else
							isearch(fp, str, &store, reg_file[j], atoi(max));
						j++;
					}
				}
				else
				{
					if(!number(max))
						printf("grep:invalid max count\n");	
					while(j < count)
					{
						fp = fopen(reg_file[j], "r");
						if(fp == NULL)
							printf("grep:Cannot open the file\n");			
						else
							search(fp, str, &store, reg_file[j], atoi(max));
						j++;
					}
				}				
			}
			else
			{
				if(charsearch(&store, 'i'))
				{
					remov(&store, 'i');	
					while(j < count)
					{
						fp = fopen(reg_file[j], "r");
						if(fp == NULL)
							printf("grep:Cannot open the file\n");
						else
							isearch(fp, str, &store, reg_file[j], INT_MAX);
						j++;
					}
				}
				else
				{
					while(j < count)
					{
						fp = fopen(reg_file[j], "r");
						if(fp == NULL)
							printf("grep:Cannot open the file\n");			
						else
							search(fp, str, &store, reg_file[j], INT_MAX);
						j++;
					}
				}
			}
		}
	}
	return 0;
}
void search(FILE *fp, char *str, list *s, char *filename, int m)
{
	char line[1000];
	int count = 0, i = 0;
	long byte = 0;
	if(charsearch(s, 'h'))
		remov(s, 'h');
	if(length(s) == 0)
	{
		while(fgets(line, 1000, fp) != NULL)
		{
			if(strstr(line, str) != NULL && i < m)
			{
				print(line);	
				i++;	
			}
		}
		return;
	}
	else if(length(s) == 1)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{		
					i++;
				}
			}
			return;		
		}
		if(charsearch(s, 'H'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{
					printf("%s : ", filename);
					print(line);		
					i++;
				}
			}
			return;			
		}
		if(charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) == NULL && i < m)
				{
					print(line);	
					i++;	
				}
			}
			return;
		}
	}	
	else if(length(s) == 2)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{		
					i++;
				}
			}
			return;		
		}
		if(charsearch(s, 'H') && charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{	
					count++;	
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{
					printf("%s : ", filename);
					printf("%ld : ", byte);
					print(line);		
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'c') && charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) == NULL && i < m)
				{
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) == NULL && i < m)
				{
					printf("%ld : ", byte);
					print(line);		
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) == NULL && i < m)
				{
					printf("%s : ", filename);
					print(line);		
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
	}
	else if(length(s) == 3)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{		
					i++;
				}
			}
			return;		
		}
		if(charsearch(s, 'H') && charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b') && charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) == NULL && i < m)
				{
					printf("%s : ", filename);
					printf("%ld : ", byte);
					print(line);		
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b') && charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
	}
	else if(length(s) == 4)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) != NULL && i < m)
				{		
					i++;
				}
			}
			return;		
		}
		else
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(strstr(line, str) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
	}
}

void isearch(FILE *fp, char *str, list *s, char *filename, int m)
{
	char line[1000], cline[1000], cstr[500], *x, *y;
	int count = 0, i = 0;
	long byte = 0;
	if(charsearch(s, 'h'))
		remov(s, 'h');
	y = iconvert(str, cstr);
	if(length(s) == 0)
	{
		while(fgets(line, 1000, fp) != NULL)
		{
			x = iconvert(line, cline);
			if(strstr(x, y) != NULL && i < m)
			{
				print(line);	
				i++;	
			}
		}
		return;
	}
	else if(length(s) == 1)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{	
					i++;	
				}
			}
			return;
		}
		if(charsearch(s, 'H'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{
					printf("%s : ", filename);
					print(line);	
					i++;	
				}
			}
			return;			
		}
		if(charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{
					printf("%ld : ", byte);
					print(line);	
					i++;	
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) == NULL && i < m)
				{
					print(line);	
					i++;	
				}
			}
			return;
		}
	}	
	else if(length(s) == 2)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{
					i++;	
				}
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{
					printf("%s : ", filename);
					printf("%ld : ", byte);
					print(line);		
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'c') && charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) == NULL && i < m)
				{
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) == NULL && i < m)
				{
					printf("%ld : ", byte);
					print(line);	
					i++;	
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) == NULL && i < m)
				{
					printf("%s : ", filename);
					print(line);		
					i++;
				}
			}
			return;
		}
	}
	else if(length(s) == 3)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{	
					i++;	
				}
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b') && charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) == NULL && i < m)
				{
					printf("%s : ", filename);
					printf("%ld : ", byte);
					print(line);	
					i++;	
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b') && charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
	}
	else if(length(s) == 4)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) != NULL && i < m)
				{
					i++;	
				}
			}
			return;
		}
		else
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(strstr(x, y) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
	}
}

void wsearch(FILE *fp, char *str, list *s, char *filename, int m)
{
	char line[1000];
	int count = 0, i = 0;
	long byte = 0;
	if(charsearch(s, 'h'))
		remov(s, 'h');
	if(length(s) == 0)
	{
		while(fgets(line, 1000, fp) != NULL)
		{
			if(wordcompare(line, str) != NULL && i < m)
			{
				print(line);
				i++;	
			}
		}
		return;
	}
	else if(length(s) == 1)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{
					i++;	
				}
			}
			return;
		}
		if(charsearch(s, 'H'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{
					printf("%s : ", filename);
					print(line);	
					i++;
				}
			}
			return;			
		}
		if(charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) == NULL && i < m)
				{
					print(line);
					i++;	
				}
			}
			return;
		}
	}	
	else if(length(s) == 2)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{
					i++;	
				}
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{	
					count++;	
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{
					printf("%s : ", filename);
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'c') && charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) == NULL && i < m)
				{
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) == NULL && i < m)
				{
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) == NULL && i < m)
				{
					printf("%s : ", filename);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
	}
	else if(length(s) == 3)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{
					i++;	
				}
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b') && charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) == NULL && i < m)
				{
					printf("%s : ", filename);
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b') && charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
	}
	else if(length(s) == 4)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) != NULL && i < m)
				{
					i++;	
				}
			}
			return;
		}
		else
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				if(wordcompare(line, str) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
	}
}
void iwsearch(FILE *fp, char *str, list *s, char *filename, int m)
{
	char line[1000], cline[1000], cstr[500], *x, *y;
	int count = 0, i = 0;
	long byte = 0;
	if(charsearch(s, 'h'))
		remov(s, 'h');
	y = iconvert(str, cstr);
	if(length(s) == 0)
	{
		while(fgets(line, 1000, fp) != NULL)
		{
			x = iconvert(line, cline);
			if(wordcompare(x, y) != NULL && i < m)
			{
				print(line);
				i++;
			}
		}
		return;
	}
	else if(length(s) == 1)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{
					i++;
				}
			}
			return;
		}
		if(charsearch(s, 'H'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{			
				x = iconvert(line, cline);	
				if(wordcompare(x, y) != NULL && i < m)
				{	
					printf("%s : ", filename);
					print(line);	
					i++;
				}
			}
			return;			
		}
		if(charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) == NULL && i < m)
				{
					print(line);
					i++;	
				}
			}
			return;
		}
	}	
	else if(length(s) == 2)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{
					i++;
				}
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{	
					count++;	
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{
					printf("%s : ", filename);
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'c') && charsearch(s, 'b'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) == NULL && i < m)
				{
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) == NULL && i < m)
				{
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) == NULL && i < m)
				{
					printf("%s : ", filename);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
	}
	else if(length(s) == 3)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{
					i++;
				}
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'b') && charsearch(s, 'c') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%d\n", count);
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b') && charsearch(s, 'v'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) == NULL && i < m)
				{
					printf("%s : ", filename);
					printf("%ld : ", byte);
					print(line);	
					i++;
				}
				byte = ftell(fp);
			}
			return;
		}
		if(charsearch(s, 'H') && charsearch(s, 'b') && charsearch(s, 'c'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
	}
	else if(length(s) == 4)
	{
		if(charsearch(s, 'q'))
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) != NULL && i < m)
				{
					i++;
				}
			}
			return;
		}
		else
		{
			while(fgets(line, 1000, fp) != NULL)
			{
				x = iconvert(line, cline);
				if(wordcompare(x, y) == NULL && i < m)
				{	
					count++;
					i++;
				}
			}
			printf("%s : ", filename);
			printf("%d\n", count);
			return;
		}
	}
}
void print(char *line)
{
	int i = 0;
	while(line[i] != '\0')
	{
		putchar(line[i]);
		i++;
	}
}
char *iconvert(char *line, char *cline)
{
	int i = 0;
	while(line[i] != '\0')
	{
		if(line[i] >= 65 && line[i] <= 90)
		{
			 cline[i] = line[i] + 32;
		}
		else
		{	
			cline[i] = line[i];
		}
		i++;
	}
	cline[i] = '\0';
	return cline;
}
int number(char *c)
{
	int i = 0;
	while(c[i] != '\0')
	{
		if(!(isdigit(c[i])))
			return 0;
		i++;
	}
	return 1;
}
char *wordcompare(char *line, char *str)
{
	char *c;
	int i, j;
	i = j = 0;
	while(line[i] != '\0')
	{
		if(line[i] == str[j] && (i == 0 || !(isalnum(line[i - 1])) && line[i - 1] != '_'))
		{
			c = &line[i];
			while(line[i] != '\0' && str[j] != '\0')
			{
				if(line[i] == str[j])
				{
					i++;
					j++;
				}
				else
					break;
			}
			if(str[j] == '\0')
			{
				if((!(isalnum(line[i])) && line[i] != '_'))
				{
					return c;
				}
			}
			j = 0;
		}
		i++;
	}
	return NULL;
}
void recursive(char *location, char *string, list *s, int max)
{
	FILE *f3;
	char loc[1000], str[50][1000], i = 0;
	DIR *p;
	struct dirent *d;
	p = opendir(location);
	if(p == NULL)
	{
		return;
	}
	while((d = readdir(p)) != NULL)
	{
		if(strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0)
		{
			if(d->d_type == DT_REG)
			{
				strcat(str[i], location);
				strcat(str[i], "/");
				strcat(str[i], d->d_name);
				if(charsearch(s, 'w'))
				{
					remov(s, 'w');
					if(charsearch(s, 'm'))
					{
						remov(s, 'm');
						if(charsearch(s, 'i'))
						{
							remov(s, 'i');
							f3 = fopen(str[i], "r");
							if(f3 != NULL)
							{
								iwsearch(f3, string, s, str[i], max); 
								fclose(f3);
							}
							enlist(s, 'i');
						}
						else
						{
							f3 = fopen(str[i], "r");;
							if(f3 != NULL)
							{
								wsearch(f3, string, s, str[i], max); 
								fclose(f3);
							}
						}
						enlist(s, 'm');
					}	
					else
					{
						if(charsearch(s, 'i'))
						{
							remov(s, 'i');
							f3 = fopen(str[i], "r");
							if(f3 != NULL)
							{
								iwsearch(f3, string, s, str[i], INT_MAX); 
								fclose(f3);
							}
							enlist(s, 'i');
						}
						else
						{
							f3 = fopen(str[i], "r");
							if(f3 != NULL)
							{
								wsearch(f3, string, s, str[i], INT_MAX); 
								fclose(f3);
							}
						}
					}
					enlist(s, 'w');
				}
				else
				{
					if(charsearch(s, 'm'))
					{
						remov(s, 'm');
						if(charsearch(s, 'i'))
						{
							remov(s, 'i');
							f3 = fopen(str[i], "r");
							if(f3 != NULL)
							{
								isearch(f3, string, s, str[i], max); 
								fclose(f3);
							}
							enlist(s, 'i');
						}
						else
						{
							f3 = fopen(str[i], "r");
							if(f3 != NULL)
							{
								search(f3, string, s, str[i], max); 
								fclose(f3);
							}
						}						
						enlist(s, 'm');
					}
					else
					{
						if(charsearch(s, 'i'))
						{
							remov(s, 'i');
							f3 = fopen(str[i], "r");
							if(f3 != NULL)
							{
								isearch(f3, string, s, str[i], INT_MAX); 
								fclose(f3);
							}
							enlist(s, 'i');
						}
						else
						{
							f3 = fopen(str[i], "r");
							if(f3 != NULL)
							{
								search(f3, string, s, str[i], INT_MAX); 
								fclose(f3);
							}
						}
					}
				}
				i++;
			}			
			if(d->d_type == DT_DIR)
			{
				strcpy(loc, location);
				strcat(loc, "/");
				strcat(loc, d->d_name);
				i++;
				recursive(loc, string, s, max);
			}
		}
	}	
	closedir(p);
} 





		 
	
