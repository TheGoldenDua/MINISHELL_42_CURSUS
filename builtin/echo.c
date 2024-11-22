#include "../mini.h"

void free_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

void msh_echo_n(char **args)
{
    int newline;
    int i;
    int j;

    newline = 1;
    i = 0;
    while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
    {
        j = 2;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] == '\0')
        {
            newline = 0;
            i++;
        }
        else
            break ; 
    }
    while (args[i])
    {
        write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
}

void msh_echo(char **args)
{
    if (!args[0])
    {
        write(STDOUT_FILENO, "\n", 1);
        return ;
    }
    if (ft_strncmp(args[0], "$?", 2) == 0)
    {
        extern char *g_global_status;
        write(STDERR_FILENO, g_global_status, ft_strlen(g_global_status));
        write(STDOUT_FILENO, "\n", 1);
        return ;
    }
    msh_echo_n(args);
}