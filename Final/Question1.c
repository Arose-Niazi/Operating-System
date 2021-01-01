// Author : Muhammad Arose Niazi FA18_BSE_010

/*
  Includes
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
  Defines
*/
#define INPUT   0
#define OUTPUT  1

/*
  Working
*/
int main(void)
{
  int myPipe[2]; 
  if (pipe(myPipe) == -1) //Creating the pipe
  {
    perror("failed to pipe");
    return 1;
  }
  if(fork() != 0) //Creating fork
  {
    /*
      Parent Process
    */
    dup2(myPipe[OUTPUT], STDOUT_FILENO);
    close(myPipe[INPUT]);
    close(myPipe[OUTPUT]);
    execl("/bin/sh", "/bin/sh", "-c", "grep mon /etc/passwd", NULL);
  }
  else
  {
    /*
      Child Process
    */
    waitpid(getppid(), (int *)-1, WNOHANG); //Waiting for parent process to finish. (-1 is aboslute value)
    dup2(myPipe[INPUT], STDIN_FILENO);
    close(myPipe[INPUT]);
    close(myPipe[OUTPUT]);
    execl("/bin/wc", "wc", NULL);
  }
  return 0;
}