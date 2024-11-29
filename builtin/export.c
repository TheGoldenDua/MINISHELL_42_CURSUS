#include "../mini.h"

void validate_export(char *str)
{
    int i = 0;
    int j;

    while (str[i])
    {
        if (!ft_isalnum(str[i]))
        {
            j = i + 1;
            while (str[j])
            {
                if (str[j] == '=')
                {
                    printf("minishell: export: not a valid identifier\n");
                    set_status(1);
                    return;
                }
                j++;
            }
        }
        i++;
    }
}

char *extract_key(char *str)
{
    int i = 0;
    char *key;

    while (str[i] && str[i] != '=')
        i++;

    key = malloc(sizeof(char) * (i + 1));
    if (!key)
        return (NULL);

    i = 0;
    while (str[i] && str[i] != '=')
    {
        key[i] = str[i];
        i++;
    }
    key[i] = '\0';
    return (key);
}

char *extract_value(char *str, t_envManager *envManager)
{
    int i = 0;
    int j = 0;
    char *value;

    while (str[i] && str[i] != '=')
        i++;
    i++;  // skip =

    if (str[i] == ' ')
        return (ft_strdup(""));

    value = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
    if (!value)
        return (NULL);

    while (str[i])
    {
        value[j] = str[i];
        j++;
        i++;
    }
    value[j] = '\0';
    expand_2(&value, envManager->envp);//to do
    return (value);
}

void add_new_variable(t_envManager *envManager, char *str)
{
    int i = 0;
    int j = 0;
    char **new_env;

    check_str(str); //to_do

    while (envManager->envp[j])
        j++;

    new_env = malloc(sizeof(char *) * (j + 2));
    if (!new_env)
        return;

    i = 0;
    while (envManager->envp[i])
    {
        new_env[i] = ft_strdup(envManager->envp[i]);
        i++;
    }
    new_env[i++] = ft_strdup(str);
    new_env[i] = NULL;
    ft_env_ro(&envManager);//to do
    envManager->envp = new_env;
}

void manage_export(t_envManager *envManager, char *str)
{
    int i = 0;
    char *key;
    char *value;

    if (!str)
    {
        while (envManager->envp[i])
            printf("declare -x %s\n", envManager->envp[i++]);
        set_status(0);
        return;
    }

    if (!ft_strchr(str, '='))
        return;

    validate_export(str);

    key = extract_key(str);
    value = extract_value(str, envManager);

    if (key)
        update_env(envManager, key, value);
    else
        add_new_variable(envManager, str);

    free(key);
    free(value);
    set_status(0);
}