#ifndef WILDCARD_H
#define WILDCARD_H

# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
#include <stdbool.h>

int	is_match(char *text, char *pattern);
char **get_files_in_directory(void);
char **expand_wildcard(const char *pattern);
bool contains_wildcard(const char *word);
bool contains_env(const char *word);

#endif