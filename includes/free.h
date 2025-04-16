/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:17:24 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:17:25 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "tokenizer.h"

void	free_tree(t_tree_node **root);
void	free_cmd(t_cmd *cmd);
void	*free_mul_p(void *p1, void *p2, void *p3, char **p4);
void	*free_array(char **arr);
void	free_gvars(void);
#endif