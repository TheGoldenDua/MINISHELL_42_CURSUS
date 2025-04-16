/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_bin_joining.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:44 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:45 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*build_full_path(t_line path, char *cmd)
{
	char	*tmp_path;
	char	*full_path;

	full_path = ft_substr(path.s, 0, path.count);
	tmp_path = ft_strjoin(full_path, "/");
	free(full_path);
	full_path = ft_strjoin(tmp_path, cmd);
	free(tmp_path);
	return (full_path);
}

char	*validate_binary_path(t_line path, char *cmd)
{
	struct stat	file_stat;
	char		*full_path;

	if (path.count == 0)
		full_path = ft_strdup(cmd);
	else
		full_path = build_full_path(path, cmd);
	if (stat(full_path, &file_stat) == 0 && file_stat.st_mode & S_IFREG
		&& file_stat.st_mode & S_IXUSR)
	{
		return (full_path);
	}
	free(full_path);
	return (NULL);
}

char	*find_binary_path(char *bin_name, char *env_path)
{
	t_line	path_segment;
	char	*full_path;
	size_t	i;

	path_segment.s = env_path;
	path_segment.count = 0;
	if (env_path == NULL)
		return (validate_binary_path(path_segment, bin_name));
	i = 0;
	while (env_path && env_path[i])
	{
		if (env_path[i] == ':')
		{
			full_path = validate_binary_path(path_segment, bin_name);
			if (full_path)
				return (full_path);
			path_segment.s = env_path + i + 1;
			path_segment.count = 0;
		}
		else
			path_segment.count++;
		i++;
	}
	return (validate_binary_path(path_segment, bin_name));
}

int	get_cmd_path(t_cmd *cmd)
{
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], F_OK))
		{
			perror(cmd->args[0]);
			return (127);
		}
		if (access(cmd->args[0], X_OK))
		{
			perror(cmd->args[0]);
			return (126);
		}
		cmd->binary_path = cmd->args[0];
	}
	else
	{
		cmd->binary_path = find_binary_path(cmd->args[0],
				get_env_value("PATH"));
		if (cmd->binary_path == NULL)
		{
			display_error(cmd->args[0], "command not found");
			return (127);
		}
	}
	return (0);
}
