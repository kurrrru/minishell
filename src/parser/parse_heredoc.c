/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:53:27 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/12/01 20:45:56 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	heredoc_read(t_redirect *redirect,
				int heredoc_fd[2], t_config *config);
static void	eof_warning(t_redirect *redirect);
static void	heredoc_read_loop(t_redirect *redirect,
				int heredoc_fd[2], t_config *config);

int	parse_heredoc(t_redirect *redirect, t_config *config)
{
	int		heredoc_fd[2];

	if (pipe(heredoc_fd) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	if (heredoc_read(redirect, heredoc_fd, config) != EXIT_SUCCESS)
		return (close(heredoc_fd[0]), close(heredoc_fd[1]),
			config->exit_status);
	close(heredoc_fd[1]);
	redirect->heredoc_fd = heredoc_fd[0];
	return (EXIT_SUCCESS);
}

static int	heredoc_read(t_redirect *redirect,
				int heredoc_fd[2], t_config *config)
{
	pid_t	pid;

	set_heredoc_handler();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		close(heredoc_fd[0]);
		set_heredoc_child_handler();
		del_quote(redirect->file);
		heredoc_read_loop(redirect, heredoc_fd, config);
		close(heredoc_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &config->exit_status, 0);
		config->exit_status = extract_status(config->exit_status);
		if (config->exit_status == 130)
			return (ft_putchar_fd('\n', STDOUT_FILENO), config->exit_status);
	}
	return (EXIT_SUCCESS);
}

static void	eof_warning(t_redirect *redirect)
{
	ft_putstr_fd("warning: here-document \
delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(redirect->file, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

static void	heredoc_read_loop(t_redirect *redirect,
				int heredoc_fd[2], t_config *config)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			eof_warning(redirect);
		if (ft_strcmp(line, redirect->file) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_env_heredoc_content(line, config);
		if (!expanded)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(expanded, heredoc_fd[1]);
		free(line);
		free(expanded);
	}
}
