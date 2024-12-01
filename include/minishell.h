/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:27:13 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 10:31:40 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "config.h"
# include "signals.h"
# include "exec.h"
# include "util.h"
# include "macro.h"
# include "include.h"

void	main_loop(t_config *config,
			char *input_data, t_node *root, t_data *data);

#endif