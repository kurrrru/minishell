/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:48:11 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 13:49:32 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	lexer(const char *input_line, t_data *data)
{
	int	status;

	status = lexer_split(input_line, data);
	if (status != EXIT_SUCCESS)
		return (status);
	assign_token_type(data);
	return (EXIT_SUCCESS);
}
