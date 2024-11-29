/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:34:47 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/28 23:34:55 by nkawaguc         ###   ########.fr       */
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
	if (node->argv)
	{
		i = -1;
		while (++i < node->arg_num)
			free(node->argv[i]);
		free(node->argv);
	}
	if (node->redirect)
	{
		i = -1;
		while (++i < node->redirect_num)
		{
			free(node->redirect[i].file);
			if (node->redirect[i].heredoc_fd != -1)
				close(node->redirect[i].heredoc_fd);
		}
		free(node->redirect);
	}
	free(node);
}
