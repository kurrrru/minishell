/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paren_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:50:27 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 15:54:05 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_node	*parse_paren_right(t_data *data, t_parse_helper *ps,
	t_config *config, t_node *root)
{
	ps->paren_open--;
	if (ps->paren_open < 0)
	{
		ft_putendl_fd("Syntax error: unmatched `)'", STDERR_FILENO);
		config->exit_status = EXIT_INVALID_INPUT;
		free_tree(root);
		return (NULL);
	}
	if (ps->index > 0 && data->token_arr[ps->index - 1].type == PAREN_LEFT)
	{
		ft_putendl_fd("Syntax error: unexpected `)'", STDERR_FILENO);
		config->exit_status = EXIT_INVALID_INPUT;
		free_tree(root);
		return (NULL);
	}
	return (root);
}
