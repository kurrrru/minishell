/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_heredoc_content.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:38:00 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 21:51:31 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static int	find_next_valid_dollar(const char *word, t_lexer_flag *flag);
static int	find_end_of_env(const char *word);
static char	*append_word(char *expanded, const char *word,
				int len, t_config *config);
static char	*append_env_word(char *expanded, const char *word,
				int len, t_config *config);

// wordはfreeされない。
char	*expand_env_heredoc_content(const char *word, t_config *config)
{
	t_lexer_flag	flag;
	int				i;
	char			*expanded;

	flag.dquote = 0;
	flag.squote = 0;
	expanded = ft_strdup("");
	if (!expanded)
	{
		return (perror("malloc"), NULL);
	}
	while (word[0])
	{
		i = find_next_valid_dollar(word, &flag);
		expanded = append_word(expanded, word, i, config);
		if (!expanded)
			return (NULL);
		if (!word[i])
			break ;
		word += i;
		i = find_end_of_env(word + 1);
		expanded = append_env_word(expanded, word + 1, i, config);
		if (!expanded)
			return (NULL);
		word += i + 1;
	}
	return (expanded);
}

static char	*append_word(char *expanded, const char *word,
				int len, t_config *config)
{
	char	*temp;
	char	*new_expanded;

	if (len == 0)
		return (expanded);
	new_expanded = ft_substr(word, 0, len);
	if (!new_expanded)
	{
		perror("malloc");
		config->exit_status = EXIT_FAILURE;
		free(expanded);
		return (NULL);
	}
	temp = expanded;
	expanded = ft_strjoin(expanded, new_expanded);
	free(temp);
	free(new_expanded);
	return (expanded);
}

static int	find_next_valid_dollar(const char *word, t_lexer_flag *flag)
{
	int	i;

	(void)flag;
	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && (ft_isalpha(word[i + 1]) || word[i + 1] == '_'
				|| word[i + 1] == '?'))
			return (i);
		i++;
	}
	return (i);
}

static int	find_end_of_env(const char *word)
{
	int	i;

	if (word[0] == '?')
		return (1);
	i = 0;
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		i++;
	return (i);
}

static char	*append_env_word(char *expanded, const char *word,
				int len, t_config *config)
{
	char	*key;
	char	*env_value;
	char	*new_expanded;

	key = ft_substr(word, 0, len);
	if (!key)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), free(expanded), NULL);
	}
	env_value = find_env(key, config);
	if (!env_value)
		return (free(key), free(expanded), NULL);
	new_expanded = ft_strjoin(expanded, env_value);
	free(key);
	free(expanded);
	free(env_value);
	if (!new_expanded)
	{
		perror("malloc");
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	return (new_expanded);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_config	config;
// 	char		*token_to_expand = "$USER$PATH$HOME$PWD$OLDPWD$?";
// 	char		*expanded;

// 	(void)argc;
// 	(void)argv;
// 	if (init_config(&config, envp) == EXIT_FAILURE)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	config.last_exit_status = 123;
// 	expanded = expand_env(token_to_expand, &config);
// 	if (!expanded)
// 	{
// 		fprintf(stderr, "expand_env failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	del_quote(expanded);
// 	printf("%s\n", expanded);
// 	free(expanded);
// 	free_config(&config);
// 	return (config.exit_status);
// }
