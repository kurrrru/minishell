/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paren_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:07:15 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 16:15:29 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	consecutive_parentheses_error(t_node *root, t_config *config);
static void	unexpected_parentheses_error(t_node *root, t_config *config);

t_node	*parse_paren_left(t_data *data, t_parse_helper *ps,
	t_config *config, const int depth)
{
	t_node	*root;
	t_node	*sub_tree;

	(void)depth;
	root = ps->node;
	if (ps->index > 0 && data->token_arr[ps->index - 1].type == PAREN_RIGHT)
	{
		consecutive_parentheses_error(root, config);
		return (NULL);
	}
	ps->paren_open++;
	ps->index++;
	sub_tree = parse_data(data, ps, config, 0);
	if (sub_tree == NULL)
		return (free_tree(root), NULL);
	if (root == NULL)
		root = sub_tree;
	else if (root->type == NODE_COMMAND)
	{
		unexpected_parentheses_error(root, config);
		return (free_tree(sub_tree), NULL);
	}
	else
		root->right = sub_tree;
	return (root);
}

static void	consecutive_parentheses_error(t_node *root, t_config *config)
{
	ft_putendl_fd("Syntax error: unexpected `(' after `)'", STDERR_FILENO);
	config->exit_status = EXIT_INVALID_INPUT;
	free_tree(root);
}

static void	unexpected_parentheses_error(t_node *root, t_config *config)
{
	ft_putendl_fd("Syntax error: unexpected parentheses", STDERR_FILENO);
	config->exit_status = EXIT_INVALID_INPUT;
	free_tree(root);
}
