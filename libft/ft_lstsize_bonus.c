/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:31:48 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/04/25 19:40:59 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	size_t	size;

	tmp = lst;
	size = 0;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
