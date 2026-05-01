#include <stdio.h>  // printf, fprintf
#include <stdlib.h> // malloc, free, exit

int main(int argc, char const *argv[])
{
    cshell_loop();

    return 0;
}

void cshell_loop()
{
    // Ponteiro para o início da string digitada pelo usuário
    char *line;
    // Ponteiro para um array de strings (cada posição é uma palavra do comando)
    // Ex: "ls -la /home" → args[0]="ls", args[1]="-la", args[2]="/home"
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