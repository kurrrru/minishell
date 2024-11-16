/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:14:35 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 22:18:44 by nkawaguc         ###   ########.fr       */
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

int	run_node(t_node *node, int in_fd, int out_fd, t_config *config);
int	run_tree(t_node *root, int in_fd, int out_fd, t_config *config);

#endif
