#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

//Function Prototypes:
void printError(char *string);
void printSuccess(char *string);
void cd(char *newdir, char *curdir);


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRESET "\033[0m"
