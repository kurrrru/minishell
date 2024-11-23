/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:56:17 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 21:48:48 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// The type of error will be stored in config->exit_status.
// If no error occurs, config->exit_status will be EXIT_SUCCESS.
void	parser(t_node **root, t_data *data, t_config *config)
{
	t_parse_helper	helper;

	helper.index = 0;
	helper.paren_open = 0;
	config->exit_status = EXIT_SUCCESS;
	*root = parse_data(data, &helper, config, 0);
	if (*root == NULL && config->exit_status != EXIT_SUCCESS)
		return ;
	if (helper.paren_open != 0)
	{
		ft_putendl_fd("Syntax error: unmatched `('", STDERR_FILENO);
		config->exit_status = EXIT_INVALID_INPUT;
		return ;
	}
}
