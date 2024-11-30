/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:07:35 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 17:38:46 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"

volatile sig_atomic_t	g_signal;

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
