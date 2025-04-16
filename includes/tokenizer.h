/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:17:10 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 05:00:54 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "environment.h"
# include "shell.h"
# include "structs.h"
# define SYN_ERR "syntax error."
# define SYN_QUOTE "unclosed quote."
# define SYN_BRACE "unclosed brace."
# define HERE_DOC_FNAME_ERROR "Can't get create temporary here_doc file."
# define ERR_REDIRECT "File or here_doc delimiter required."

typedef enum e_expansion_state
{
	NORMAL_STATE,
	DOUBLEQ_STATE,
	SINGLEQ_STATE,
}			t_expansion_state;

typedef enum e_expansion_type
{
	EXPAND_VARS = (1 << 1),
	REM_QUOTES = (1 << 2)
}			t_expansion_type;

// Tree Builder:
t_tree_node	*create_node(int type);
void		node_add(t_tree_node **parent, t_tree_node *child);
void		insert_child(t_tree_node *parent, t_tree_node *child);
t_tree_node	*string_node_ad(t_tree_node *root, t_tokenizer *tokenizer);
t_token		*cmd_fill(t_tree_node **root, t_token *token,
				t_tokenizer *tokenizer, int as_child);

// tokenizer:
t_tree_node	**line_parse(char *line, t_tree_node **root);

// tokenizer_utils:
t_tree_node	*tree_node_find_by_type(t_tree_node *root, t_node_type type);
t_tree_node	*new_node_link(t_tree_node **root, int type, int as_child);
int			logic_op_link(t_tree_node **root, t_tokenizer *tokenizer,
				t_token *token, int as_child);
t_tree_node	*argv_node_link(t_tree_node *curr_cmd, t_tokenizer *tokenizer);
void		*error_syntax(char *line);
int			line_get(t_tokenizer *tokenizer, t_line *s, char *special_char_set);

// tokenizer:
t_token		get_next_token(t_tokenizer *tokenizer, int ignore_spaces);

// token_utils:
t_tokenizer	new_tokenizer(char *line);
void		trim_spaces(t_tokenizer *tokenizer);
int			token_is_cmd(t_token token);
int			token_is_redirect(t_token token);

/* here_doc */
int			string_randomize(char *str, int rand_fd);
int			interrupt_here_doc_handle(int stdin_dup);
void		here_doc_add(t_tree_node *node);
t_tree_node	**here_docs_retrieve(t_tree_node **root);
int			line_write_next_here_doc(t_tree_node *node, int write);

/* t_line utils */
int			has_chars(t_line string, char *charset);

/* string expansion */
char		*str_expand(t_line string, t_expansion_type expansion_type);
char		*str_expansion(t_line string, t_expansion_type expansion_type);
size_t		expanded_string_length(t_line string,
				t_expansion_type expansion_type);
size_t		key_count_parse(const char *s);
void		variable_value_copy(char *res, t_line *string, size_t *i);
int			chars_count_num(long n);
char		**args_expansion(char **args, size_t *count);
void		var_len_count(t_line string, size_t *i, size_t *len);

#endif