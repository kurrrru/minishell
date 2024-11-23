/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:04:36 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/05/03 17:52:02 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_rec(char **to_free, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		free(to_free[i]);
	free(to_free);
}

static int	split_fill(char **ret, int cnt, const char *s, char c)
{
	int	block;
	int	pos;

	block = -1;
	pos = 0;
	while (++block < cnt)
	{
		while (s[pos] == c && s[pos] != '\0')
			pos++;
		s = s + pos;
		pos = 0;
		while (s[pos] != '\0' && s[pos] != c)
			pos++;
		ret[block] = (char *)malloc((pos + 1) * sizeof(char));
		if (!ret[block])
			return (free_rec(ret, block), 0);
		pos = 0;
		while (s[pos] != '\0' && s[pos] != c)
		{
			ret[block][pos] = s[pos];
			pos++;
		}
		ret[block][pos] = '\0';
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	int		cnt;
	int		i;
	char	**ret;

	if (!s)
		return (NULL);
	i = 0;
	cnt = (s[0] != c && s[0] != '\0');
	while (s[0] != '\0' && s[++i] != '\0')
		cnt += (s[i - 1] == c && s[i] != c);
	ret = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[cnt] = NULL;
	if (!split_fill(ret, cnt, s, c))
		return (NULL);
	return (ret);
}
