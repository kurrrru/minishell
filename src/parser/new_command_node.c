/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_command_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:05:33 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 14:17:13 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_node	*new_command_node(t_token token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (perror("malloc"), NULL);
	node->left = NULL;
	node->right = NULL;
	node->type = NODE_COMMAND;
	if (token.token == NULL)
		node->command = NULL;
	else
	{
		node->command = ft_strdup(token.token);
		if (node->command == NULL)
			return (perror("malloc"), free(node), NULL);
	}
	node->redirect_num = 0;
	node->redirect_capacity = 2;
	node->redirect = ft_calloc(node->redirect_capacity, sizeof(t_redirect));
	node->arg_num = 0;
	node->arg_capacity = 2;
	node->argv = ft_calloc(node->arg_capacity, sizeof(char *));
	if (node->redirect == NULL || node->argv == NULL)
		return (perror("malloc"), free_tree(node), NULL);
	return (node);
}
