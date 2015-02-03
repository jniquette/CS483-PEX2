#include "shell.h"




int main(void){
  char* curdir = malloc(PATH_MAX);
  char* input = malloc(CMD_MAX);
 // node* commandList;
  char** commands;
  printf("-------\n");
  
  while(1){
  
  printf("$");  
  
  //Get and parse user input as a linked list. The first node is the command,
  //the rest are arguments.
  fgets(input, CMD_MAX, stdin);
  commands = parseCommand(input, commands);
  printf("back to main\n");
  
    if(strcmp(commands[0], "exit") == 0){
      printf("Goodbye!\n\n");fflush(stdout);
      return 0;   
    }
    else if(strcmp(commands[0], "cd") == 0){
      cd(commands[1], curdir);
    }
    else{
      printError("unimplemented");fflush(stdout);
    }

    //Need to free commands and commands*
  }

  return 0;
}

char** parseCommand(char *input, char** commands){//node *commandList){
  //printf("In parseCommand\n");  
  char* thisArg;
  commands = malloc(sizeof(char*));
  //list_destroy(commandList);
  char constant[5];
  
  
  //Cut trailing \n from input
  input = strtok(input, "\n");
  
  int i = 0;
  
  while(1){
    printf("Attempting to insert a command\n");
    if(i == 0)
      thisArg = strtok(input, " ");
    else
      thisArg = strtok(NULL, " ");
    if(thisArg == NULL){//strcmp(thisArg, "") == 0){
      printf("it's null\n");
      break;
    }
    else{
      commands[i] = thisArg;
      printf("inserted %s\n", commands[i]);
      i++;
      printf("Reallocating for %d string*'s, total size is %d\n", i, (int) (i*sizeof(char*)));
      commands = realloc(commands, i*sizeof(char*));
    }
  }
  
  return commands;
}

void cd(char *newdir, char *curdir){
  if(strcmp(newdir, "~") == 0 || strcmp(newdir, "") == 0){
    newdir = getenv("HOME");
  }
  if(chdir(newdir))
    printError("Couldn't Change Directory");
  else{
    curdir = (char*) (long) getcwd(curdir, PATH_MAX);
    printSuccess(curdir);
  }
}

void printError(char *string){
  printf(KRED "[ERROR]" KRESET "\t%s\n", string);
}

void printSuccess(char *string){
  printf(KGRN "[OK]" KRESET "\t%s\n", string);
}
