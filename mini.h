#ifndef MINI_H
#define MINI_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include "../libft/libft.h"

void msh_echo(char **args);
void msh_echo_n(char **args);
void free_args(char **args);
void msh_cd(char args, char **env, t_envManager **env_p);
void msh_cd_path(char *args);
void msh_cd_oldpwd(char ***env);
void msh_cd_home(char *args, char *home);
void msh_check_home(char *home);
void ft_pwd(void);
 
typedef struct s_envManager
{
    char        **envp;
    bool        path;
}t_envManager;

#endif