/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:36:29 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 17:37:51 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"

extern sig_atomic_t	g_signal;

void	idle_handler(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	rl_replace_line("", 0);
	rl_done = 1;
}

void	heredoc_handler(int signum)
{
	(void) signum;
	g_signal = SIGINT;
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	exec_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
