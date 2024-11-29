/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:54:57 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/29 23:55:11 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "config.h"
# include "include.h"
# include "macro.h"
# include "util.h"

void	idle_handler(int signum);
void	set_idle_handler(void);
void	exec_handler(int signum);
void	set_exec_child_handler(void);
void	set_exec_handler(void);
void	set_heredoc_handler(void);
void	set_heredoc_child_handler(void);
void	heredoc_child_handler(int signum);
void	check_core_dump(int status);

#endif