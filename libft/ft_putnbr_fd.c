/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:49:51 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/04/19 01:49:51 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
	ft_putstr_fd(memo + i - (n < 0), fd);
}
