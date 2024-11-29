/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_is_match.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:15:30 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 16:23:47 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static void	free_dp(int **dp, const int m);
static void	is_match_loop(const char *text, const char *pattern, int **dp);

int	is_match(const char *text, const char *pattern)
{
	const int	m = ft_strlen(text);
	const int	n = ft_strlen(pattern);
	int			**dp;
	int			i;
	int			result;

	dp = ft_calloc(m + 1, sizeof(int *));
	i = -1;
	while (++i <= m)
		dp[i] = ft_calloc(n + 1, sizeof(int));
	if (text[0] == '.' && pattern[0] != '.')
		return (free_dp(dp, m), FALSE);
	dp[0][0] = TRUE;
	i = 0;
	while (++i <= n)
		if (pattern[i - 1] == '*')
			dp[0][i] = dp[0][i - 1];
	is_match_loop(text, pattern, dp);
	result = dp[m][n];
	return (free_dp(dp, m), result);
}

static void	free_dp(int **dp, const int m)
{
	int	i;

	i = -1;
	while (++i <= m)
		free(dp[i]);
	free(dp);
}

static void	is_match_loop(const char *text, const char *pattern, int **dp)
{
	const int	m = ft_strlen(text);
	const int	n = ft_strlen(pattern);
	int			i;
	int			j;

	i = 0;
	while (++i <= m)
	{
		j = 0;
		while (++j <= n)
		{
			if (pattern[j - 1] == '*')
				dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
			else if (pattern[j - 1] == '?' || text[i - 1] == pattern[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = FALSE;
		}
	}
}
