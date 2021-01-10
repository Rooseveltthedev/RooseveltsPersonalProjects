#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80

int main(void) {
  char * args[MAX_LINE / 2 + 1];
  char string[MAX_LINE];
  int shouldrn = 1; /*variable used to keep program running until user calls for exit*/
  int i = 0;
  int j;
  while (shouldrn) {
    printf("osh> ");
    fflush(stdout); /*writes any unwritten data to file*/

    scanf("%[^\n]%*c", string); /*stores all characters entered as input including spaces until enter*/
    i = 0;
    int j;
    args[i] = strtok(string, " "); /*token splitting function )*/

    while (args[i] != NULL) { /*while the string is not null tokenizes each character that isnt a space*/
      i++;
      args[i] = strtok(NULL, " ");
    }

    if (strcmp(args[0], "exit") == 0) /*checks for exit input on user command*/
      break;
    if (strcmp(args[i - 1], "&") != 0) 
      pid_t pid;
      pid = fork();
      if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
      } else if (pid == 0) {
        execvp(args[0], args);
        for (int j = 0; j < i; j++)
          args[j] = NULL;
      } else {
        wait(NULL);
      }
    } else {
      pid_t pid;
      pid = fork();
      if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
      } else if (pid == 0) {
        args[i - 1] = NULL;
        execvp(args[0], args);
      } else {
        printf("\n\n");
      }
    }

  }
  return 0;
}