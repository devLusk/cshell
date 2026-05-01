#include <stdio.h>  // printf, fprintf
#include <stdlib.h> // malloc, free, exit

int main(int argc, char const *argv[])
{
    cshell_loop();

    return 0;
}

void cshell_loop()
{
    // pointer to the beginning of the string typed by the user
    char *line;
    // pointer to an array of strings (each position is a word of the command)
    // ex: "ls -la /home" → args[0]="ls", args[1]="-la", args[2]="/home"
    char **args;
    int status;

    do
    {
        print("> ");
        line = cshell_read_line();
        args = cshell_split_line();
        status = cshell_execute(args);

        free(line);
        free(args);
    } while (status);
}

#define CSHELL_RL_BUFSIZE 1024
char *cshell_read_line(void)
{
    int bufsize = CSHELL_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize); // allocates initial 1024 bytes
    int c;                                         // int instead of char because getchar can return EOF (-1)

    if (!buffer)
    {
        fprintf(stderr, "cshell: error allocating memory\n");
        exit(1);
    }

    while (1)
    {
        c = getchar(); // reads next char from keyboard

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0'; // null-terminates the string
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += CSHELL_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize); // reallocates preserving content
            if (!buffer)
            {
                fprintf(stderr, "cshell: error allocating memory\n");
                exit(1);
            }
        }
    }
}