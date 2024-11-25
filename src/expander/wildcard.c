#include "wildcard.h"

#define TRUE 1
#define FALSE 0

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static char *ft_strjoin(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return NULL;
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);

	char *result = malloc(len1 + len2 + 1);
	if (!result)
		return NULL;
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = 0;
}

void	*malloc_wrap(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(ptr, size);
	return (ptr);
}

int is_match(char *text, char *pattern) {
	int m = ft_strlen(text);
	int n = ft_strlen(pattern);
	int **dp = malloc_wrap(sizeof(int *) * (m + 1));
	for (int i = 0; i <= m; i++) {
		dp[i] = malloc_wrap(sizeof(int) * (n + 1));
	}
	if (text[0] == '.' && pattern[0] != '.') {
		for (int i = 0; i <= m; i++) {
			free(dp[i]);
		}
		free(dp);
		return 0;
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		dp[0][i] = (pattern[i - 1] == '*') ? dp[0][i - 1] : 0;
	}
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (pattern[j - 1] == '*')
				dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
			else if (pattern[j - 1] == '?' || text[i - 1] == pattern[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = 0;
		}
	}
	int result = dp[m][n];
	for (int i = 0; i <= m; i++) {
		free(dp[i]);
	}
	free(dp);
	return result;
}

bool contains_wildcard(const char *word) {
	int dquote = 0;
	int squote = 0;
	int i = 0;
	while (word[i]) {
		if ((word[i] == '"') && (squote == 0))
			dquote = 1;
		else if (word[i] == '\'' && dquote == 0)
			squote = !squote;
		else if (dquote == 0 && squote == 0 && word[i] == '*')
			return true;
		i++;
	}
	return false;
}

bool contains_env(const char *word) {
	int dquote = 0;
	int squote = 0;
	int i = 0;

	while (word[i]) {
		if (word[i] == '"' && squote == 0) {
			dquote = !dquote;
		} else if (word[i] == '\'' && dquote == 0) {
			squote = !squote;
		} else if (word[i] == '$' && squote == 0) {
			return true;
		}
		i++;
	}
	return false;
}

char **get_files_in_directory(void) {
	DIR *dir = opendir(".");
	struct dirent *entry;
	char **files = NULL;
	size_t count = 0;

	if (!dir)
		return NULL;

	while ((entry = readdir(dir)) != NULL) {
		files = realloc(files, sizeof(char *) * (count + 2));
		files[count] = strdup(entry->d_name);
		count++;
	}
	files[count] = NULL;
	closedir(dir);
	return files;
}

// char *expand_wildcard(const char *pattern) {
//	 char **files = get_files_in_directory();
//	 char *expanded = NULL;
//	 size_t i = 0;

//	 if (!files)
//		 return strdup("");
//	 while (files[i]) {
//		 if (is_match(files[i], (char *)pattern)) {
//			 if (expanded) {
//				 char *temp = expanded;
//				 expanded = ft_strjoin(ft_strjoin(expanded, " "), files[i]);
//				 free(temp);
//			 } else 
//				 expanded = strdup(files[i]);
//		 }
//		 free(files[i]);
//		 i++;
//	 }
//	 free(files);
//	 if (!expanded)
//		 return strdup("");
//	 return expanded;
// }

void	sort_strings(char **strings)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = 0;
	while (strings[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (strcmp(strings[i], strings[j]) > 0)
			{
				tmp = strings[i];
				strings[i] = strings[j];
				strings[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char **expand_wildcard(const char *pattern) {
	char **files = get_files_in_directory();
	char **expanded = NULL;
	size_t count = 0;
	size_t i = 0;

	if (!files)
		return NULL;

	while (files[i]) {
		if (is_match(files[i], (char *)pattern)) {
			expanded = realloc(expanded, sizeof(char *) * (count + 2));
			expanded[count] = strdup(files[i]);
			count++;
		}
		free(files[i]);
		i++;
	}
	free(files);

	if (expanded) {
		expanded[count] = NULL; // NULL 終端
	} else {
		// 一致するファイルがなかった場合
		expanded = malloc(sizeof(char *) * 2);
		expanded[0] = strdup(pattern); // 元のパターンを返す
		expanded[1] = NULL;
	}
	sort_strings(expanded);
	return expanded;
}

// int main(int argc, char **argv)
// {
// 	char *pattern = argc > 1 ? argv[1] : "*";
// 	char **files = expand_wildcard(pattern);
// 	int i = 0;

// 	while (files[i]) {
// 		printf("%s ", files[i]);
// 		free(files[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	free(files);
// 	return 0;
// }
