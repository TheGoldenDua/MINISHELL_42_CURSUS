/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:42:32 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:46:44 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include "shell.h"
# include "structs.h"

t_envlist	*create_nodes(char *key, char *value);
void		setup_env(const char **envp);
t_envlist	*add_env_end(t_envlist **list_head, char *key, char *value);
void		remove_env(t_envlist **env_list, char *key);
char		*get_env_value(char *key);
t_envlist	*get_env_node(char *data);
t_envlist	*add_or_update_env(char *key, char *value);
char		**generate_env_arr(void);

#endif