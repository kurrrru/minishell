/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:51:40 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 21:20:32 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void		word_after_paren_right_error(t_config *config, t_node **root);
static void		parse_malloc_error(t_node *root, t_config *config);
static t_node	*add_argv(t_token *token, t_config *config, t_node **root);
static t_node	*add_command(t_token *token, t_config *config, t_node **root);

t_node	*parse_command(t_data *data, t_parse_helper *ps, t_config *config,
			t_node **root)
{
	t_token	token;

	token = data->token_arr[ps->index];
	if (ps->index > 0 && data->token_arr[ps->index - 1].type == PAREN_RIGHT)
		return (word_after_paren_right_error(config, root), NULL);
	if (*root == NULL)
	{
		if (add_command(&token, config, root) == NULL)
			return (NULL);
	}
	else
	{
		if ((*root)->command == NULL)
		{
			(*root)->command = ft_strdup(token.token);
			if ((*root)->command == NULL)
				return (parse_malloc_error(*root, config), NULL);
		}
		else if (add_argv(&token, config, root) == NULL)
			return (NULL);
	}
	return (*root);
}

static void	word_after_paren_right_error(t_config *config, t_node **root)
{
	ft_putendl_fd("Syntax error: unexpected word after `)'", STDERR_FILENO);
	config->exit_status = EXIT_INVALID_INPUT;
	free_tree(*root);
}

static void	parse_malloc_error(t_node *root, t_config *config)
{
	perror("malloc");
	config->exit_status = EXIT_FAILURE;
	free_tree(root);
}

static t_node	*add_argv(t_token *token, t_config *config, t_node **root)
{
	if ((*root)->arg_num >= (*root)->arg_capacity)
	{
		(*root)->arg_capacity *= 2;
		(*root)->argv = ft_realloc((*root)->argv,
				sizeof(char *) * (*root)->arg_num,
				sizeof(char *) * (*root)->arg_capacity);
		if ((*root)->argv == NULL)
			return (parse_malloc_error(*root, config), NULL);
	}
	(*root)->argv[(*root)->arg_num++] = ft_strdup(token->token);
	if ((*root)->argv[(*root)->arg_num - 1] == NULL)
		return (parse_malloc_error(*root, config), NULL);
	return (*root);
}

static t_node	*add_command(t_token *token, t_config *config, t_node **root)
{
	*root = new_command_node(*token);
	if (*root == NULL)
	{
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	return (*root);
}
