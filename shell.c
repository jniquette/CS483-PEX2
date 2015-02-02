#include "shell.h"




int main(void){
printf("-------\n");
  char* curdir = malloc(PATH_MAX);
  
  cd("/usr", curdir);

  return 0;
}

void cd(char *newdir, char *curdir){
  //TODO: implement if ~ and ''
  if(chdir(newdir))
    printError("Couldn't Change Directory");
  else{
    curdir = (char*) (long) getcwd(curdir, PATH_MAX);
/*    if(strlen(dir) == 0){
      dir = realpath(".", dir);
    }*/
      printSuccess(curdir);
  }
}

void printError(char *string){
  printf(KRED "[ERROR]" KRESET "\t%s\n", string);
}

void printSuccess(char *string){
  printf(KGRN "[OK]" KRESET "\t%s\n", string);
}
