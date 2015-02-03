#include "shell.h"




int main(void){
  char* curdir = malloc(PATH_MAX);
  char* input = malloc(CMD_MAX);
  char* input_copy = malloc(CMD_MAX);
  node* history;
  char** commands;
  //printf("-------\n");
  
  while(1){
  
  printf(KCYN "$ " KRESET); 
  
  //Get and parse user input as a linked list. The first node is the command,
  //the rest are arguments.
  fgets(input, CMD_MAX, stdin);
  input_copy = strcpy(input_copy, input);
  commands = parseCommand(input, commands);
  //printf("back to main\n");
  
  
    if(strcmp(commands[0], "recall") == 0){
      if(!commands[1])
        printError("Value not specified");
      else
        commands = recall(history, atoi(commands[1]), commands);
    }
  
    if(commands[0] == NULL);
    else if(strcmp(commands[0], "exit") == 0){
      printSuccess("Goodbye!\n\n");fflush(stdout);
      exit(EXIT_SUCCESS);   
    }
    else if(strcmp(commands[0], "history") == 0){
      if(!commands[1])
        list_print_count(history, DEFAULT_HISTORY);
      else
        list_print_count(history, atoi(commands[1]));
    }
    else if(strcmp(commands[0], "cd") == 0){
      history = addToHistory(input_copy, history);
      cd(commands[1], curdir);
    }
    else{
      runCommand(commands);  
      history = addToHistory(input_copy, history);
    }

    //Need to free commands and commands*
  }

  return 0;
}

char** recall(node* history, int number, char** commands){
  printf("Will recall: %s\n", list_get(history, list_get_size(history)+1-number));
  return parseCommand(list_get(history, list_get_size(history)+1-number), commands);
}

node* addToHistory(char* input, node* history){
  if(strncmp(input, "recall", 6) == 0)
    return history;
  //Cut trailing \n from input
  input = strtok(input, "\n");
  history = list_remove(history, input);
  return list_insert_tail(history, input);
}

int runCommand(char** args){
  pid_t rtn;
	int i;
	
	rtn = fork();
	
	if (rtn < 0) {  // error
		printError("Could not create child process.");
	}
	else if (rtn == 0 ) {// child
    execvp(args[0], (char*) args);
	} else { // parent
		wait(NULL);
		printSuccess("Child complete.");
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
    //printf("Attempting to insert a command\n");
    if(i == 0)
      thisArg = strtok(input, " ");
    else
      thisArg = strtok(NULL, " ");
    if(thisArg == NULL){//strcmp(thisArg, "") == 0){
      //printf("it's null\n");
      break;
    }
    else{
      commands[i] = thisArg;
      //printf("inserted %s\n", commands[i]);
      i++;
      //printf("Reallocating for %d string*'s, total size is %d\n", i, (int) (i*sizeof(char*)));
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
