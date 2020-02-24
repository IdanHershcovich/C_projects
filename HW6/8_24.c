#include "csapp.h"
#include "csapp.c"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> 
#define N 2

int main() {
  int status, i;
  pid_t pid;

  /* Parent creates N children */
  for (i = 0; i < N; i++)
    if ((pid = fork()) == 0) {
		//write to a read only, cause error.
      strcpy("FORBIDDEN", NULL);
    }

  /* Parent reaps N children in no particular order */
  while ((pid = waitpid(-1, &status, 0)) > 0) {
    if (WIFEXITED(status))
      printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
    else if (WIFSIGNALED(status)) {
      //printing the signal
      printf("child %d terminated by signal %d\n", pid, WTERMSIG(status));
      psignal(WTERMSIG(status), NULL);
    }
    else
      printf("child %d terminated abnormally\n", pid);
  }

  /* The only normal termination is if there are no more children */
  if (errno != ECHILD)
    unix_error("waitpid error");

  exit(0);
}