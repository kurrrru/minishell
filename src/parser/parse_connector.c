/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_connector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:31:15 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 23:09:42 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	no_left_side(t_data *data, t_parse_helper *ps,
				t_config *config, t_node *root);
static void	no_right_side(t_data *data, t_parse_helper *ps,
				t_config *config, t_node *root);

t_node	*parse_connector(t_data *data, t_parse_helper *ps,
		t_config *config, const int depth)
{
	t_node	*root;
	t_node	*conn_node;

	root = ps->node;
	if (root == NULL)
		return (no_left_side(data, ps, config, root), NULL);
	conn_node = new_connector_node(data->token_arr[ps->index]);
	if (conn_node == NULL)
	{
		config->exit_status = EXIT_FAILURE;
		return (free_tree(root), NULL);
	}
	conn_node->left = root;
	root = conn_node;
	ps->index++;
	conn_node->right = parse_data(data, ps, config, depth + 1);
	if (conn_node->right == NULL)
	{
		if (config->exit_status == EXIT_SUCCESS)
			return (no_right_side(data, ps, config, root), NULL);
		return (free_tree(root), NULL);
	}
	return (root);
}

static void	no_left_side(t_data *data,
		t_parse_helper *ps, t_config *config, t_node *root)
{
	ft_putstr_fd("Syntax error: unexpected `", STDERR_FILENO);
	ft_putstr_fd(data->token_arr[ps->index].token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	config->exit_status = EXIT_INVALID_INPUT;
	free_tree(root);
}

static void	no_right_side(t_data *data, t_parse_helper *ps,
		t_config *config, t_node *root)
{
	ft_putstr_fd("Syntax error: missing command after `", STDERR_FILENO);
	ft_putstr_fd(data->token_arr[ps->index - 1].token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	config->exit_status = EXIT_INVALID_INPUT;
	free_tree(root);
}
