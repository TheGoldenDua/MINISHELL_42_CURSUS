#include "../mini.h"
#include <unistd.h>

void ft_pwd(void)
{
    char    *pwd;
 
    pwd = getcwd(NULL, 0);
    if(!pwd)
    {
        write(STDERR_FILENO, "Error retrieving current directory\n", 35);
        set_status(1);
        return ;
    }
    write(STDOUT_FILENO, pwd, ft_strlen(pwd));
    write(STDOUT_FILENO, "\n", 1);
    free(pwd);
    set_status(0);
}