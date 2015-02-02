#include "shell.h"




int main(void){
  char* curdir = malloc(PATH_MAX);
  char* input = malloc(CMD_MAX);
  node* commandList;
  printf("-------\n");
  
  while(1){
  
  printf("$");  
  
  //Get and parse user input as a linked list. The first node is the command,
  //the rest are arguments.
  fgets(input, CMD_MAX, stdin);
  commandList = parseCommand(input, commandList);
  
  //list_print(commandList);
  
  
      //printf("first item is: %s\n", commandList->data);fflush(stdout);

    if(strcmp(commandList->data, "exit") == 0){
      printf("Goodbye!\n\n");fflush(stdout);
      return 0;   
    }
    else if(strcmp(commandList->data, "cd") == 0){
      cd(commandList->next->data, curdir);
    }
    else{
      printError("unimplemented");fflush(stdout);
    }
    }

  return 0;
}

node* parseCommand(char *input, node *commandList){
  //printf("In parseCommand\n");  
  int argCount = 0;
  char* thisArg;
  //list_destroy(commandList);
  
  
  //Cut trailing \n from input
  input = strtok(input, "\n");
  
  while(1){
    if(argCount == 0)
      thisArg = strtok(input, " ");
    else
      thisArg = strtok(NULL, " ");
    //printf("thisArg: %s\n", thisArg);
    if(thisArg == NULL){
      //printf("End of the arguments\n");  
      break;
    }
    else{
      commandList = list_insert_tail(commandList, thisArg);
      //printf("added %s to arguments\n", thisArg);
      argCount++;
    }
  }
  
  return commandList;
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
