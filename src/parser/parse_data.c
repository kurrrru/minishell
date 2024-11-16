/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:21:17 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 17:23:47 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_redirect(t_token token);

t_node *parse_data(t_data *data, t_parse_helper *ps, t_config *config, const int depth)
{
	t_node	*root;

	root = NULL;
	while (ps->index < data->token_num)
	{
		t_token token = data->token_arr[ps->index];
		if (token.type == PIPE || token.type == LOGICAL_AND || token.type == LOGICAL_OR)
		{
			if ((token.type == LOGICAL_AND || token.type == LOGICAL_OR) && depth > 0)
				return (ps->index--, root);
			ps->node = root;
			root = parse_connector(data, ps, config, depth);
			if (root == NULL)
				return (NULL);
		}
		else if (token.type == PAREN_LEFT)
		{
			ps->node = root;
			root = parse_paren_left(data, ps, config, depth);
			if (root == NULL)
				return (NULL);
		}
		else if (token.type == PAREN_RIGHT)
			return (parse_paren_right(data, ps, config, root));
		else if (is_redirect(token))
		{
			if (parse_redirect(data, ps, config, &root) == NULL)
				return (NULL);
		}
		else if (token.type == WORD)
		{
			if (ps->index > 0 && data->token_arr[ps->index - 1].type == PAREN_RIGHT)
			{
				ft_putendl_fd("Syntax error: unexpected word after `)'", STDERR_FILENO);
				config->exit_status = EXIT_INVALID_INPUT;
				free_tree(root);
				return (NULL);
			}
			if (root == NULL)
			{
				root = new_command_node(token);
				if (root == NULL)
				{
					config->exit_status = EXIT_FAILURE;
					return (NULL);
				}
			}
			else
			{
				if (root->command == NULL)
				{
					root->command = ft_strdup(token.token);
					if (root->command == NULL)
					{
						perror("malloc");
						config->exit_status = EXIT_FAILURE;
						free_tree(root);
						return (NULL);
					}
				}
				else
				{
					if (root->arg_num >= root->arg_capacity)
					{
						root->arg_capacity *= 2;
						root->argv = ft_realloc(root->argv,
							sizeof(char *) * root->arg_capacity / 2, sizeof(char *) * root->arg_capacity);
					}
					root->argv[root->arg_num++] = ft_strdup(token.token);
					if (root->argv[root->arg_num - 1] == NULL)
					{
						perror("malloc");
						config->exit_status = EXIT_FAILURE;
						free_tree(root);
						return (NULL);
					}
				}
			}
		}
		ps->index++;
	}
	return root;
}

static int	is_redirect(t_token token)
{
	return (token.type == REDIRECT_IN || token.type == REDIRECT_OUT ||
			token.type == REDIRECT_APPEND || token.type == REDIRECT_HEREDOC);
}
