#include <unistd.h>
#include <stdio.h>
 
/* since pipes are unidirectional, we need two pipes.
   one for data to flow from parent's stdout to child's
   stdin and the other for child's stdout to flow to
   parent's stdin */
 
#define NUM_PIPES          2
 
#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1
 
int pipes[NUM_PIPES][2];
 
/* always in a pipe[], pipe[0] is for read and 
   pipe[1] is for write */
#define READ_FD  0
#define WRITE_FD 1
 
#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )
 
#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )
 
void doPipe()
{
    int outfd[2];
    int infd[2];
     
    // pipes for parent to write and read
    pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);
     
    if(!fork()) { //child
        printf("child\n");
        char *argv[]={ "sort", "-nr", 0};
 
        dup2(CHILD_READ_FD, STDIN_FILENO);
        //dup2(CHILD_WRITE_FD, STDOUT_FILENO);
        printf("child dupped\n");
 
        /* Close fds not required by child. Also, we don't
           want the exec'ed program to know these existed */
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);
        printf("child closed descriptors\n");
         
        printf("Going to try to execute %s\n", argv[0]);

        execv(argv[0], argv);
    } else {//parent
        printf("parent\n");
        char buffer[1024];
        int count;
 
        /* close fds not required by parent */       
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        printf("parent closed descriptors\n");
 
        //write(PARENT_WRITE_FD, read(PARENT_READ_FD, buffer, sizeof(buffer)-1), sizeof(buffer)-1);
 
        write(PARENT_WRITE_FD, "so\nmuch\nstuff\n\0", 15);
 
        // Write to child’s stdin
/*        write(PARENT_WRITE_FD, "2^32\n", 5);
  
        // Read from child’s stdout
        count = read(PARENT_READ_FD, buffer, sizeof(buffer)-1);
        if (count >= 0) {
            buffer[count] = 0;
            printf("%s", buffer);
        } else {
            printf("IO Error\n");
        }*/
    }
}
