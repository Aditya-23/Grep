Name : Aditya Mysore
Title : Grep
MIS ID : 111708038

Objective : To write the grep command

Grep : Globally search for regular expression and print out.

It looks for the specified expression and prints the line containing that 
expression.

Various options are specified to slightly modify the output.

Options : -r  -i  -v  -f  -w  -c  -m  -b -q  -H  -h

Method used:
The data structure used is list.
There are mainly four functions which search a given pattern in a given file are used which are:
search(), isearch(), wsearch(), iwsearch()
The function getopt is used to get the options from the command line and store it in a data structure : list
Using the list functions charsearch() and remov(), the appropriate function (out of the above four) is found out and that function is called.
For the -r option , a recursive function is used to access all the files in a directory and its subdirectories.
Other user defined functions used are:
1. iconvert() : To convert a string to lowercase
2. wordcompare() : To check for the existence of a word in a line
3. print() : To print a line
4. number() : To check whether a string is a number or not( is used for -m option)
5. Also other library functions such as strstr, ftell, fgets, etc.

This project contains all files needed for implementation of grep.
This project runs for all the valid combinations of the options:
-i, -w, -b, -H, -h, -c, -r, f, -m, -q
While using -r, provide the name of the directory to be searched.
