/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:34:47 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 13:36:16 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	free_node(t_node *node);

void	free_tree(t_node *root)
{
	if (root == NULL)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free_node(root);
}

static void	free_node(t_node *node)
{
	int	i;

	if (node == NULL)
		return ;
	free(node->command);
	i = -1;
	while (++i < node->arg_num)
		free(node->argv[i]);
	free(node->argv);
	i = -1;
	while (++i < node->redirect_num)
		free(node->redirect[i].file);
	free(node->redirect);
	free(node);
}
