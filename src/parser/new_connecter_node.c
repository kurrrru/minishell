/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_connecter_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:13:43 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 14:16:30 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_node	*new_connector_node(t_token token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (perror("malloc"), NULL);
	if (token.type == PIPE)
		node->type = NODE_PIPE;
	else if (token.type == LOGICAL_AND)
		node->type = NODE_LOGICAL_AND;
	else if (token.type == LOGICAL_OR)
		node->type = NODE_LOGICAL_OR;
	node->left = NULL;
	node->right = NULL;
	node->command = NULL;
	node->arg_num = 0;
	node->argv = NULL;
	node->redirect_num = 0;
	node->redirect_capacity = 2;
	node->redirect = ft_calloc(node->redirect_capacity, sizeof(t_redirect));
	if (node->redirect == NULL)
		return (perror("malloc"), free(node), NULL);
	return (node);
}
