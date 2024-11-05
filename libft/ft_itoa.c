/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 02:11:10 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/04/19 02:11:10 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	memo[12];
	int		i;
	int		sign;

	sign = (n >= 0) * 2 - 1;
	ft_memset(memo, '-', 10);
	memo[11] = '\0';
	memo[10] = n % 10 * sign + '0';
	i = 10;
	while (n <= -10 || n >= 10)
	{
		n /= 10;
		memo[--i] = n % 10 * sign + '0';
	}
	return (ft_strdup(memo + i - (n < 0)));
}
