/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:26:30 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/18 12:07:54 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static int	redirect_heredoc(t_node *node, int *in_fd, int i);
static int	redirect_in(t_node *node, int *in_fd, int i);
static int	redirect_out(t_node *node, int *out_fd, int i);
static int	redirect_append(t_node *node, int *out_fd, int i);

int	redirect_handler(t_node *node, int *in_fd, int *out_fd)
{
	int	i;

	i = -1;
	while (++i < node->redirect_num)
	{
		if (node->redirect[i].type == IN && redirect_in(node, in_fd, i))
			return (EXIT_FAILURE);
		else if (node->redirect[i].type == HEREDOC
			&& redirect_heredoc(node, in_fd, i))
			return (EXIT_FAILURE);
		else if (node->redirect[i].type == OUT
			&& redirect_out(node, out_fd, i))
			return (EXIT_FAILURE);
		else if (node->redirect[i].type == APPEND
			&& redirect_append(node, out_fd, i))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	redirect_heredoc(t_node *node, int *in_fd, int i)
{
	int	heredoc_fd[2];

	heredoc_fd[0] = -1;
	heredoc_fd[1] = -1;
	if (heredoc_read(node, heredoc_fd, i))
		return (close(heredoc_fd[0]), close(heredoc_fd[1]), EXIT_FAILURE);
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	*in_fd = heredoc_fd[0];
	if (heredoc_fd[1] != STDOUT_FILENO)
		close(heredoc_fd[1]);
	return (EXIT_SUCCESS);
}

static int	redirect_in(t_node *node, int *in_fd, int i)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	*in_fd = open(node->redirect[i].file, O_RDONLY);
	if (*in_fd == -1)
		return (perror(node->redirect[i].file), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	redirect_out(t_node *node, int *out_fd, int i)
{
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	*out_fd = open(node->redirect[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out_fd == -1)
		return (perror(node->redirect[i].file), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	redirect_append(t_node *node, int *out_fd, int i)
{
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	*out_fd = open(node->redirect[i].file,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out_fd == -1)
		return (perror(node->redirect[i].file), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
