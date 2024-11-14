/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:09:29 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/14 23:09:35 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->token_num)
		free(data->token_arr[i].token);
	free(data->token_arr);
}
