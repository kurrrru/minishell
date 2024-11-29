/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:07:35 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 00:07:36 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"

volatile sig_atomic_t	g_signal;

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

void	set_heredoc_child_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_IGN;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGQUIT, &sig, NULL);
	sig.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sig, NULL);
}

void	set_heredoc_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_IGN;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	set_idle_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = idle_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
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

void	check_core_dump(int status)
{
	if (WCOREDUMP(status))
	{
		g_signal = SIGQUIT;
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	set_exec_child_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_DFL;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	set_exec_handler(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = exec_handler;
	sigaction(SIGINT, &sig, NULL);
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}
