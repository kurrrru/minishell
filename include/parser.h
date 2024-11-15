
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:20:33 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/14 21:00:51 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "config.h"
# include "macro.h"
# include "include.h"
# include "util.h"

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_LOGICAL_AND,
	NODE_LOGICAL_OR,
	NODE_COMMAND,
}	t_node_type;

typedef enum e_redirect_type
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type	type;
	char			*file;
}	t_redirect;

typedef struct s_node
{
	t_node_type		type;
	char			*command;
	int				redirect_num;
	int				redirect_capacity;
	t_redirect		*redirect;
	int				arg_num;
	int				arg_capacity;
	char			**argv;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_parse_helper
{
	int	index;
	int	paren_open;
}	t_parse_helper;

void	parser(t_node **root, t_data *data, t_config *config);
void	dump_node(t_node *node, int depth);
void	dump_tree(t_node *root);
void	free_tree(t_node *root);

#endif
