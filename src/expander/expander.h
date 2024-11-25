#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "parser.h"
# include "wildcard.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
#include <readline/readline.h>

char *append_segment(char *rtn, const char *word, int start, int end);
char **del_quote(char *word);
char *expander(const char *word, int *index);

#endif