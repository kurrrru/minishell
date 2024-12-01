/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_core_dump.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:38:31 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 17:49:46 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"

extern sig_atomic_t	g_signal;

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
