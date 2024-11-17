/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:54:55 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/17 23:12:39 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	heredoc_read(t_node *node, int heredoc_fd[2], int i)
{
	char	*line;

	if (heredoc_fd[0] != -1 && heredoc_fd[0] != STDIN_FILENO)
		close(heredoc_fd[0]);
	if (heredoc_fd[1] != -1 && heredoc_fd[1] != STDOUT_FILENO)
		close(heredoc_fd[1]);
	if (pipe(heredoc_fd) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("bash: warning: here-document \
delimited by end-of-file (wanted `", STDERR_FILENO);
			ft_putstr_fd(node->redirect[i].file, STDERR_FILENO);
			ft_putendl_fd("')", STDERR_FILENO);
			return (EXIT_SUCCESS);
		}
		if (ft_strcmp(line, node->redirect[i].file) == 0)
			return (free(line), EXIT_SUCCESS);
		ft_putendl_fd(line, heredoc_fd[1]);
		free(line);
	}
	return (EXIT_SUCCESS);
}
