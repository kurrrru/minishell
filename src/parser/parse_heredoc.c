/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:54:55 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 21:51:50 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int heredoc_read(t_redirect *redirect, int heredoc_fd[2], t_config *config);

int	parse_heredoc(t_redirect *redirect, t_config *config)
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
	if (heredoc_read(redirect, heredoc_fd, config))
		return (close(heredoc_fd[0]), close(heredoc_fd[1]), EXIT_FAILURE);
	close(heredoc_fd[1]);
	redirect->heredoc_fd = heredoc_fd[0];
	return (EXIT_SUCCESS);
}

static int heredoc_read(t_redirect *redirect, int heredoc_fd[2], t_config *config)
{
    pid_t pid;

    set_heredoc_handler();
    close(heredoc_fd[0]);
    pid = fork();
    if (pid == -1)
        return (perror("fork"), EXIT_FAILURE);
    if (pid == 0)
    {
        char *line;
		char	*expanded;
		set_heredoc_child_handler();
		del_quote(redirect->file);
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
			expanded = expand_env_heredoc_content(line, config);
			if (!expanded)
				return (free(line), EXIT_FAILURE);
			ft_putendl_fd(expanded, heredoc_fd[1]);
			free(expanded);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(heredoc_fd[1]);
        waitpid(pid, &config->exit_status, 0);
        config->exit_status = extract_status(config->exit_status);
    }
    return EXIT_SUCCESS;
}

// static int	heredoc_read(t_redirect *redirect, int heredoc_fd[2])
// {
// 	char	*line;

// 	while (1)
// 	{
// 		set_heredoc_handler();
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			ft_putstr_fd("bash: warning: here-document 
// delimited by end-of-file (wanted `", STDERR_FILENO);
// 			ft_putstr_fd(redirect->file, STDERR_FILENO);
// 			ft_putendl_fd("')", STDERR_FILENO);
// 			return (EXIT_SUCCESS);
// 		}
// 		if (ft_strcmp(line, redirect->file) == 0)
// 			return (free(line), EXIT_SUCCESS);
// 		ft_putendl_fd(line, heredoc_fd[1]);
// 		free(line);
// 	}
// 	return (EXIT_SUCCESS);
// }
