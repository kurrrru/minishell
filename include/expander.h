/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 02:24:21 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 19:15:45 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "config.h"
# include "lexer.h"
# include "util.h"
# include "macro.h"
# include "include.h"

char	*expand_env(const char *word, t_config *config);

char	*find_env(const char *key, t_config *config);

void	del_quote(char *word);

int		is_match(const char *text, const char *pattern);

char	**expand_wildcard(const char *pattern, t_config *config);

#endif
