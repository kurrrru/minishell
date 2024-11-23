/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:54:55 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/18 19:23:37 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	heredoc_read(t_redirect *redirect, int heredoc_fd[2]);

int	parse_heredoc(t_redirect *redirect)
{
	int		heredoc_fd[2];
	// char	*file;

	// file = redirect->file;
	// redirect->file = del_quote(redirect->file);
	// free(file);
	// if (!redirect->file)
	// 	return (EXIT_FAILURE);
	if (pipe(heredoc_fd) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	// set heredoc sighandler ?
	if (heredoc_read(redirect, heredoc_fd))
		return (close(heredoc_fd[0]), close(heredoc_fd[1]), EXIT_FAILURE);
	close(heredoc_fd[1]);
	redirect->heredoc_fd = heredoc_fd[0];
	return (EXIT_SUCCESS);
}

static int	heredoc_read(t_redirect *redirect, int heredoc_fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("bash: warning: here-document \
delimited by end-of-file (wanted `", STDERR_FILENO);
			ft_putstr_fd(redirect->file, STDERR_FILENO);
			ft_putendl_fd("')", STDERR_FILENO);
			return (EXIT_SUCCESS);
		}
		if (ft_strcmp(line, redirect->file) == 0)
			return (free(line), EXIT_SUCCESS);
		ft_putendl_fd(line, heredoc_fd[1]);
		free(line);
	}
	return (EXIT_SUCCESS);
}
