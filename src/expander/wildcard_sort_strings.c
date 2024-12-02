/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort_strings.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:48:26 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/12/02 02:06:51 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static void	quick_sort_ch(char **arr, int left, int right);
static void	ft_swap_ch(char **a, char **b);

void	sort_strings(char **strings)
{
	int		len;

	len = 0;
	while (strings[len])
		len++;
	quick_sort_ch(strings, 0, len);
}

static void	quick_sort_ch(char **arr, int left, int right)
{
	char	*pivot;
	int		i;
	int		j;

	if (left + 1 >= right)
		return ;
	ft_swap_ch(&arr[left], &arr[(left + right) / 2]);
	pivot = arr[left];
	i = left + 1;
	j = right - 1;
	while (1)
	{
		while (i < right && ft_strcmp(arr[i], pivot) < 0)
			i++;
		while (left <= j && ft_strcmp(pivot, arr[j]) < 0)
			j--;
		if (i >= j)
			break ;
		ft_swap_ch(&arr[i], &arr[j]);
	}
	if (left < j)
		ft_swap_ch(&arr[left], &arr[j]);
	quick_sort_ch(arr, left, j);
	quick_sort_ch(arr, j + 1, right);
}

static void	ft_swap_ch(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
