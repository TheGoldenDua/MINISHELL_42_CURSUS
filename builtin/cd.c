#include "../mini.h"

void msh_check_home(char *home)
{
    if (!home)
    {
        write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
        set_status(1);
        return;
    }
}

void msh_cd_home(char *args, char *home)
{
    char *tmp;

    msh_check_home(home);
    tmp = ft_strtrim(args, "~");
    if (!tmp)
        return ;
    args = ft_strjoin(home, tmp); 
    free(tmp);
    if (chdir(home) == -1)
    {
        write(STDERR_FILENO, "minishell: cd: Failed to navigate to home\n", 42);
        set_status(1);
    }
}

void msh_cd_oldpwd(char ***env)
{
    char *oldpwd;

    *oldpwd = find_env((*env), "OLDPWD=");
    if (!oldpwd)
    {
        write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 30);
        set_status(1);
        return ;
    }

    if (chdir(oldpwd) == -1)
    {
        perror("cd");
        set_status(1);
        return ;
    }
    write(STDOUT_FILENO, oldpwd, strlen(oldpwd)); 
    write(STDOUT_FILENO, "\n", 1);
}

void msh_cd_path(char *args)
{
    if (chdir(args) == -1)
    {
        write(STDERR_FILENO, "minishell: cd: ", 15);
        write(STDERR_FILENO, args, strlen(args));
        write(STDERR_FILENO, ": ", 2);
        write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
        set_status(1);
    }
}

void msh_cd(char args, char **env, t_envManager **env_p)
{
    char    *home;
    char    *pwd;
    char    *old_pwd;
    char cwd[1024];

    home = find_env((*env), "HOME="); 
    old_pwd = getcwd(cwd, sizeof(cwd)); 

    if (!args)
    {
        msh_check_home(home);
        if (home)
            chdir(home);
    }
    else if (ft_strchr(args, '~'))
        msh_cd_home(args, home);
    else if (ft_strcmp(args, "-") == 0)
        msh_cd_oldpwd(env);
    else 
        msh_cd_path(args);
    old_pwd = ft_strjoin("OLDPWD=", old_pwd);
    pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
    ft_export(env_p, old_pwd);            
    ft_export(env_p, pwd);                
    free(old_pwd);
    free(pwd);
    set_status(0);      
}                                                                                                                                                                                                                                                                                          