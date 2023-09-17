#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main()
{
    pid_t child_pid; /* Declare child_pid here at the beginning of the block */
    char input[MAX_INPUT_SIZE];
    int interactive = 1;

    /* 
     * Assume interactive mode by default 
     */

    while (1)
    {
        if (interactive)
        {
            printf("($) ");
            /*
             * Display a simple shell prompt
             */
            fflush(stdout);
            /*
             * Flush the output buffer
             */
            if (fgets(input, sizeof(input), stdin) == NULL)
            {
                perror("fgets");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (fgets(input, sizeof(input), stdin) == NULL)
            {
                break;
                /*
                 * Exit the loop when there's no more input
                 */
            }
        }

        /*
         * Remove newline character from input
         */
        input[strcspn(input, "\n")] = '\0';

        /*
         * Create a child process
         */
        child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0)
        {
 	     /*
             * Child process
             * Execute the command entered by the user
             */

          
            char **args_copy = malloc(4 * sizeof(char *));
            if (args_copy == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            args_copy[0] = "/bin/sh";
            args_copy[1] = "-c";
            args_copy[2] = input;
            args_copy[3] = NULL;

            execvp("/bin/sh", args_copy);
            perror("execvp");

            free(args_copy);

            /*
             * This line is reached if execvp fails
             */
            exit(EXIT_FAILURE);
        }
        else
        {
            /*
             * Parent process
             */
            int status;
            waitpid(child_pid, &status, 0);
            if (WIFEXITED(status))
            {
                if (interactive)
                {
                    printf("Child process exited with status %d\n", WEXITSTATUS(status));
                }
            }
        }
    }

    return 0;
}
