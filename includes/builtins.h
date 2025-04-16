/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:42:26 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:48:54 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "environment.h"
# include "structs.h"

# include <fcntl.h>

int			ft_echo(t_cmd cmd);
int			go_to_home(t_cmd *cmd);
int			change_directory(char *path, char *old_pwd, t_cmd *cmd);
int			go_to_path(char *path, t_cmd *cmd);
int			return_to_oldpwd(t_cmd *cmd);
int			ft_cd(t_cmd cmd);
int			ft_pwd(t_cmd cmd);
int			ft_export(t_cmd cmd);
t_envlist	**get_sort_env_lst(void);
int			update_env_vars(char *old_pwd, t_cmd *cmd);
int			print_exported_env(t_cmd cmd);
void		swap_lst(t_envlist **p1, t_envlist **p2);
char		*parse_key_mode(char *arg, int *append);
int			ft_unset(t_cmd cmd);
int			ft_env(t_cmd cmd);
int			ft_exit(t_cmd cmd);
int			key_valid(char *key);
int			key_not_valid(char *cmd, char *key);

#endif