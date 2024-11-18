/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:14:35 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/18 00:32:45 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include "config.h"
# include "util.h"
# include "macro.h"
# include "include.h"

typedef struct s_exec
{
	char	*command;
	char	**argv;
	int		in_fd;
	int		out_fd;
	char	**envp;
}	t_exec;

typedef struct s_pipe_helper
{
	int		in_fd;
	int		out_fd;
	int		*pipe_fd;
	pid_t	*pid;
}	t_pipe_helper;

int		run_node(t_node *node, int in_fd, int out_fd, t_config *config);
int		run_tree(t_node *root, int in_fd, int out_fd, t_config *config);

int		exec_logical_connectors(t_node *node, int in_fd,
			int out_fd, t_config *config);

int		exec_pipe(t_node *node, int in_fd, int out_fd, t_config *config);
int		exec_pipe_left_cmd(t_node *node, t_pipe_helper ph,
			t_config *config);
int		exec_pipe_left_con(t_node *node, t_pipe_helper ph,
			t_config *config);

int		exec_command(t_node *node, int in_fd, int out_fd, t_config *config);
char	**make_envp(t_config *config);
char	*get_path(char *command);
int		is_directory(const char *path);

int		redirect_handler(t_node *node, int *in_fd, int *out_fd);
int		heredoc_read(t_node *node, int heredoc_fd[2], int i);

void	perror_exit(char *message, int exit_status);

#endif