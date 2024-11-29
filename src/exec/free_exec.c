/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:22:29 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 00:04:46 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	free_exec(t_exec *exec)
{
	if (exec->command)
		free(exec->command);
	if (exec->argv)
		free_2d(exec->argv);
	if (exec->envp)
		free_2d(exec->envp);
}
