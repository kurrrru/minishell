/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:21:17 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 23:08:04 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node *parse_data(t_data *data, t_parse_helper *ps, t_config *config, const int depth)
{
	t_node *root = NULL;

	while (ps->index < data->token_num)
	{
		t_token token = data->token_arr[ps->index];
		if (token.type == PIPE || token.type == LOGICAL_AND || token.type == LOGICAL_OR)
		{
			if ((token.type == LOGICAL_AND || token.type == LOGICAL_OR) && depth > 0)
			{
				ps->index--;
				return root;
			}
			ps->node = root;
			root = parse_connector(data, ps, config, depth);
			if (root == NULL)
				return (NULL);
		}
		else if (token.type == PAREN_LEFT)
		{
			if (ps->index > 0 && data->token_arr[ps->index - 1].type == PAREN_RIGHT)
			{
				ft_putendl_fd("Syntax error: unexpected `(' after `)'", STDERR_FILENO);
				config->exit_status = EXIT_INVALID_INPUT;
				free_tree(root);
				return (NULL);
			}
			ps->paren_open++;
			ps->index++;
			t_node *sub_tree = parse_data(data, ps, config, 0);
			if (sub_tree == NULL)
			{
				free_tree(root);
				return (NULL);
			}
			if (root == NULL)
				root = sub_tree;
			else
			{
				if (root->type == NODE_PIPE || root->type == NODE_LOGICAL_AND || root->type == NODE_LOGICAL_OR)
				{
					t_node *conn_node = root;
					conn_node->right = sub_tree;
				}
				else
				{
					ft_putendl_fd("Syntax error: unexpected parentheses", STDERR_FILENO);
					config->exit_status = EXIT_INVALID_INPUT;
					free_tree(sub_tree);
					free_tree(root);
					return (NULL);
				}
			}
		}

		else if (token.type == PAREN_RIGHT)
		{
			ps->paren_open--;
			if (ps->paren_open < 0)
			{
				ft_putendl_fd("Syntax error: unmatched `)'", STDERR_FILENO);
				config->exit_status = EXIT_INVALID_INPUT;
				free_tree(root);
				return (NULL);
			}
			if (ps->index > 0 && data->token_arr[ps->index - 1].type == PAREN_LEFT)
			{
				ft_putendl_fd("Syntax error: unexpected `)'", STDERR_FILENO);
				config->exit_status = EXIT_INVALID_INPUT;
				free_tree(root);
				return (NULL);
			}
			return root;
		}
		else if (token.type == REDIRECT_IN || token.type == REDIRECT_OUT ||
					token.type == REDIRECT_APPEND || token.type == REDIRECT_HEREDOC)
		{
			if (root == NULL)
			{
				root = new_command_node((t_token){.token = NULL, .type = WORD});
				if (root == NULL)
				{
					config->exit_status = EXIT_FAILURE;
					return (NULL);
				}
			}
			ps->index++;
			if (ps->index < data->token_num && data->token_arr[ps->index].type == WORD)
			{
				t_token file_token = data->token_arr[ps->index];
				t_redirect redirect;

				if (token.type == REDIRECT_IN)
					redirect.type = IN;
				else if (token.type == REDIRECT_OUT)
					redirect.type = OUT;
				else if (token.type == REDIRECT_HEREDOC)
					redirect.type = HEREDOC;
				else if (token.type == REDIRECT_APPEND)
					redirect.type = APPEND;
				redirect.file = ft_strdup(file_token.token);
				if (redirect.file == NULL)
				{
					perror("malloc");
					config->exit_status = EXIT_FAILURE;
					free_tree(root);
					return (NULL);
				}
				if (root->redirect_num >= root->redirect_capacity)
				{
					root->redirect_capacity *= 2;
					root->redirect = ft_realloc(root->redirect,
						sizeof(t_redirect) * root->redirect_capacity / 2,
						sizeof(t_redirect) * root->redirect_capacity);
					if (root->redirect == NULL)
					{
						perror("malloc");
						config->exit_status = EXIT_FAILURE;
						free_tree(root);
						return (NULL);
					}
				}
				root->redirect[root->redirect_num++] = redirect;
			}
			else
			{
				ft_putendl_fd("Syntax error: missing file for redirect", STDERR_FILENO);
				config->exit_status = EXIT_INVALID_INPUT;
				free_tree(root);
				return (NULL);
			}
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
