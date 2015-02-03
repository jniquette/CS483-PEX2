#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "list.c"

//Function Prototypes:
void printError(char *string);
void printSuccess(char *string);
void cd(char *newdir, char *curdir);
char** parseCommand(char *input, char** commands);
int runCommand(char** args);
node* addToHistory(char* input, node* history);
void recall(node* commands, int number);

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRESET "\033[0m"

#define CMD_MAX 1024
#define DEFAULT_HISTORY 100
