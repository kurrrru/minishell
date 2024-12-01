/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:26:29 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 21:12:09 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static bool	is_num(const char *str);

void	bi_exit(t_exec exec, t_config *config)
{
	if (config->is_child == 0)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (exec.argv[1])
	{
		if (is_num(exec.argv[1]))
		{
			config->last_exit_status = ft_atoi(exec.argv[1]);
			if (exec.argv[2])
			{
				ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
				if (config->exit_status == EXIT_SUCCESS)
					config->last_exit_status = EXIT_FAILURE;
			}
		}
		else
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(exec.argv[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			config->last_exit_status = EXIT_INVALID_INPUT;
		}
	}
	exit(config->last_exit_status);
}

static bool	is_num(const char *str)
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
	if (!ft_isdigit(*str))
		return (false);
	while (ft_isdigit(*str))
	{
		if (ret > LONG_MAX / 10 || (ret == LONG_MAX / 10 && *str > '7'))
			return (false);
		if (ret < LONG_MIN / 10 || (ret == LONG_MIN / 10 && *str > '8'))
			return (false);
		ret = ret * 10l + (*str++ - '0') * sign;
	}
	return (*str == '\0');
}
