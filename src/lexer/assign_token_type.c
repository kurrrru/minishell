/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:12:46 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/05 23:13:34 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	assign_token_type(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->token_num)
	{
		data->token_arr[i].type = WORD;
		if (ft_strcmp(data->token_arr[i].token, "|") == 0)
			data->token_arr[i].type = PIPE;
		else if (ft_strcmp(data->token_arr[i].token, "<") == 0)
			data->token_arr[i].type = REDIRECT_IN;
		else if (ft_strcmp(data->token_arr[i].token, ">") == 0)
			data->token_arr[i].type = REDIRECT_OUT;
		else if (ft_strcmp(data->token_arr[i].token, ">>") == 0)
			data->token_arr[i].type = REDIRECT_APPEND;
		else if (ft_strcmp(data->token_arr[i].token, "<<") == 0)
			data->token_arr[i].type = REDIRECT_HEREDOC;
		else if (ft_strcmp(data->token_arr[i].token, "(") == 0)
			data->token_arr[i].type = PAREN_LEFT;
		else if (ft_strcmp(data->token_arr[i].token, ")") == 0)
			data->token_arr[i].type = PAREN_RIGHT;
		else if (ft_strcmp(data->token_arr[i].token, "&&") == 0)
			data->token_arr[i].type = LOGICAL_AND;
		else if (ft_strcmp(data->token_arr[i].token, "||") == 0)
			data->token_arr[i].type = LOGICAL_OR;
	}
}
