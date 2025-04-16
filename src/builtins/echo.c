/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:10 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:16:11 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	parse_flags(char **args, int *i)
{
	int	print_nl;
	int	j;

	print_nl = TRUE;
	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] == '\0')
		{
			(*i)++;
			print_nl = FALSE;
		}
		else
			break ;
	}
	return (print_nl);
}

void	print_echo_arguments(char **args, int i, int outfd, int print_nl)
{
	while (args[i])
	{
		write(outfd, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(outfd, " ", 1);
		i++;
	}
	if (print_nl == TRUE)
		write(outfd, "\n", 1);
}

int	check_echo_options(t_cmd cmd)
{
	int	print_nl;
	int	i;

	i = 1;
	print_nl = parse_flags(cmd.args, &i);
	print_echo_arguments(cmd.args, i, cmd.outfd, print_nl);
	return (0);
}

int	ft_echo(t_cmd cmd)
{
	if (cmd.ac == 1)
	{
		write(cmd.outfd, "\n", 1);
		return (0);
	}
	return (check_echo_options(cmd));
}
