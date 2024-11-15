/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:39:33 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 14:22:34 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

// int	main(void)
// {
// 	char		*input_line;
// 	t_data		data;
// 	int			i;
// 	const char	*type[] = {"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT",
// 		"REDIRECT_HEREDOC", "REDIRECT_APPEND", "PAREN_LEFT",
// 		"PAREN_RIGHT", "LOGICAL_AND", "LOGICAL_OR"};
// 	int			status;

// 	while (1)
// 	{
// 		input_line = readline("lexer$ ");
// 		if (!input_line)
// 			break ;
// 		status = lexer(input_line, &data);
// 		if (status != EXIT_SUCCESS)
// 			continue ;
// 		printf("  token_num: %d\n", data.token_num);
// 		i = -1;
// 		while (++i < data.token_num)
// 			printf("  [%s], %s\n", data.token_arr[i].token,
// 				type[data.token_arr[i].type]);
// 		free_data(&data);
// 	}
// 	return (EXIT_SUCCESS);
// }

/*
test cases

`a b c`, `a b  c`, `a  b c`, `a  b  c`
{"a", "b", "c"}

`ls`, `   ls`, `ls  `, `  ls  `
{"ls"}

`ls | cat`, `ls|cat`, `  ls| cat`
{"ls", "|", "cat"}

`ls >> file`, `ls>>file`, `  ls>> file`
{"ls", ">>", "file"}

`< file`, `<file`, `  < file`
{"<", "file"}

`"l"'s'`
{"ls"}

` 'l'"s"`
{'l'"s"}

`"  "' ' ' '"  "`
{"\"  \"' '", "' '\"  \""}

`echo "a b c"`
{"echo", "\"a b c\""}

`|||&&&`
{"||", "|", "&&", "&"}

*/
