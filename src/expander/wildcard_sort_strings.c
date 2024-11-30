/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:48:26 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 17:48:31 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

void	sort_strings(char **strings)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = 0;
	while (strings[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(strings[i], strings[j]) > 0)
			{
				tmp = strings[i];
				strings[i] = strings[j];
				strings[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
