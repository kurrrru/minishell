/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:48:11 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/18 12:19:34 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	lexer(const char *input_line, t_data *data, t_config *config)
{
	data->token_num = 0;
	if (ft_strlen(input_line) == 0)
		return (config->exit_status);
	config->exit_status = lexer_split(input_line, data);
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	assign_token_type(data);
	return (EXIT_SUCCESS);
}
