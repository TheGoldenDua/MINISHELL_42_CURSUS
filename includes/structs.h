/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:17:15 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:17:16 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define SHELL_NAME "sh-13"
# define ALLOCATION_ERR "Malloc failed. exiting shell."
# define DOUBLEQ '"'
# define SINGLEQ '\''
# define DA_DEFAULT_CAPACITY 5
# define BUFFER_SIZE 1024
# include "libft.h"
# include <assert.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_dynarr
{
	void				*data;
	size_t				count;
	size_t				arr_size;
	size_t				data_size;
}						t_dynarr;

typedef struct s_line
{
	const char			*s;
	size_t				count;
}						t_line;

typedef struct s_envlist
{
	char				*key;
	char				*value;
	int					is_set;
	struct s_envlist	*next;
}						t_envlist;

typedef enum e_token_type
{
	T_EOF = 0x00,
	STR = 0x01,
	PIPE = 0x02,
	REDIRECT_IN = 0x04,
	REDIRECT_OUT = 0x08,
	APPEND = 0x10,
	HERE_DOC = 0x20
}						t_token_type;

typedef enum e_node_type
{
	N_CMD = 0x00,
	N_PIPE = 0x02,
	N_STR = 0x01,
	N_REDIRECT_IN = 0x04,
	N_REDIRECT_OUT = 0x08,
	N_APPEND = 0x10,
	N_HERE_DOC = 0x20
}						t_node_type;

typedef struct s_token
{
	char				c;
	t_token_type		type;
}						t_token;

typedef struct s_tree_node
{
	void				*data;
	int					here_doc_fd;
	size_t				childs_count;
	size_t				list_count;
	t_line				token_str;
	t_node_type			type;
	struct s_tree_node	*children;
	struct s_tree_node	*next;
}						t_tree_node;

typedef struct s_tokenizer
{
	const char			*buffer;
	size_t				pos;
	size_t				count;
}						t_tokenizer;

typedef enum e_cmd_type
{
	CMD_BUILTIN,
	CMD_BINARY,
	CMD_SUBSHELL
}						t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type			type;
	char				**args;
	char				*binary_path;
	int					infd;
	int					outfd;
	int					pipe_read;
	int					status;
	size_t				ac;
}						t_cmd;

t_dynarr				create_dynarr(size_t size);
t_dynarr				*resize_array(t_dynarr *array);
t_dynarr				*add_to_arr(t_dynarr *array, void *element);
int						ft_isspace(char c);
void					close_here_docs(void);
void					malloc_error(void *p1, void *p2, char **p3, t_cmd *cmd);
void					exit_with_status(t_cmd *cmd, int exit_value);
void					print_strerr(t_line str, char *line);

#endif