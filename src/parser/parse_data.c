/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:21:17 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 21:27:40 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_logical(t_token token);
static int	is_redirect(t_token token);

t_node	*parse_data(t_data *data, t_parse_helper *ps,
	t_config *config, const int depth)
{
	t_node	*root;
	t_token	token;

	root = NULL;
	while (ps->index < data->token_num)
	{
		token = data->token_arr[ps->index];
		if (is_logical(token) && depth > 0)
			return (ps->index--, root);
		ps->node = root;
		if (token.type == PIPE || is_logical(token))
			root = parse_connector(data, ps, config, depth);
		else if (token.type == PAREN_LEFT)
			root = parse_paren_left(data, ps, config, depth);
		else if (token.type == PAREN_RIGHT)
			return (parse_paren_right(data, ps, config, root));
		else if (is_redirect(token))
			root = parse_redirect(data, ps, config, &root);
		else if (token.type == WORD)
			root = parse_command(data, ps, config, &root);
		if (root == NULL)
			return (NULL);
		ps->index++;
	}
	return (root);
}

static int	is_redirect(t_token token)
{
	return (token.type == REDIRECT_IN || token.type == REDIRECT_OUT
		|| token.type == REDIRECT_APPEND || token.type == REDIRECT_HEREDOC);
}

static int	is_logical(t_token token)
{
	return (token.type == LOGICAL_AND || token.type == LOGICAL_OR);
}
