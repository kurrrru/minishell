/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:16:26 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 00:07:58 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void		set_redirect_type(t_redirect *redirect, t_token token);
static t_node	*new_redirect(t_token token, t_token file_token, t_node **root,
					t_config *config);
static int		double_redirect(t_config *config, t_node **root);

t_node	*parse_redirect(t_data *data, t_parse_helper *ps,
	t_config *config, t_node **root)
{
	t_token	token;

	token = data->token_arr[ps->index];
	if (*root == NULL)
	{
		*root = new_command_node((t_token){NULL, WORD});
		if (*root == NULL)
		{
			config->exit_status = EXIT_FAILURE;
			return (NULL);
		}
	}
	ps->index++;
	if (ps->index < data->token_num && data->token_arr[ps->index].type == WORD)
		return (new_redirect(token, data->token_arr[ps->index], root, config));
	else
	{
		ft_putendl_fd("Syntax error: missing file for redirect",
			STDERR_FILENO);
		config->exit_status = EXIT_INVALID_INPUT;
		return (free_tree(*root), NULL);
	}
	return (*root);
}

static void	set_redirect_type(t_redirect *redirect, t_token token)
{
	if (token.type == REDIRECT_IN)
		redirect->type = IN;
	else if (token.type == REDIRECT_OUT)
		redirect->type = OUT;
	else if (token.type == REDIRECT_APPEND)
		redirect->type = APPEND;
	else if (token.type == REDIRECT_HEREDOC)
		redirect->type = HEREDOC;
}

static t_node	*new_redirect(t_token token, t_token file_token, t_node **root,
	t_config *config)
{
	t_redirect	redirect;

	set_redirect_type(&redirect, token);
	redirect.file = ft_strdup(file_token.token);
	redirect.heredoc_fd = -1;
	if (redirect.file == NULL)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), free_tree(*root), NULL);
	}
	if ((*root)->redirect_num >= (*root)->redirect_capacity - 1)
	{
		if (double_redirect(config, root) == EXIT_FAILURE)
			return (NULL);
	}
	if (redirect.type == HEREDOC)
	{
		config->exit_status = parse_heredoc(&redirect, config);
		if (config->exit_status != EXIT_SUCCESS)
			return (free_tree(*root), free(redirect.file),
				close(redirect.heredoc_fd), NULL);
	}
	(*root)->redirect[(*root)->redirect_num++] = redirect;
	return (*root);
}

static int	double_redirect(t_config *config, t_node **root)
{
	(*root)->redirect_capacity *= 2;
	(*root)->redirect = ft_realloc_redirect((*root)->redirect,
			sizeof(t_redirect) * (*root)->redirect_capacity / 2,
			sizeof(t_redirect) * (*root)->redirect_capacity);
	if ((*root)->redirect == NULL)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("ft_realloc"), free_tree(*root), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
