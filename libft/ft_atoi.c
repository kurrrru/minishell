/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/03/15 16:52:33 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/03/15 16:52:33 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	ret;
	long	sign;

	ret = 0l;
	sign = 1l;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1l;
	while (ft_isdigit(*str))
	{
		if (ret > LONG_MAX / 10 || (ret == LONG_MAX / 10 && *str > '7'))
			return ((int)LONG_MAX);
		if (ret < LONG_MIN / 10 || (ret == LONG_MIN / 10 && *str > '8'))
			return ((int)LONG_MIN);
		ret = ret * 10l + (*str++ - '0') * sign;
	}
	return ((int)ret);
}
