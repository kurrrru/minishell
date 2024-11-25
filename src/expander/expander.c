/*
・環境変数として有効/無効な文字のチェック
・エラーの出力
*/

/*
dquotation内でのsquotationはリテラルとして扱われる
squotation内でのdquotationはリテラルとして扱われる

sigle quotation内では$は展開されない
dquotation内では展開される
"2"
*/

#include "exec.h"
#include "wildcard.h"
#include <readline/readline.h>
#include <readline/history.h>

int ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
int ft_isalnum(int c)
{
	return (ft_isalpha(c) || (c >= '0' && c <= '9'));
}
char *ft_strjoin(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return NULL;
	//strlen, strcpy, strcatを置き換える
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);

	char *result = malloc(len1 + len2 + 1);
	if (!result)
		return NULL;
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = 0;
}

static void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_bzero(ptr, size);
	return (ptr);
}

static char	*xstrndup(const char *s, size_t n)
{
	char	*new_s;
	size_t	i;

	new_s = (char *)xmalloc(n + 1);
	i = 0;
	while (i < n && s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char *append_segment(char *rtn, const char *word, int start, int end)
{
	char *segment = xstrndup(&word[start], end - start);
	char *temp = rtn;
	rtn = ft_strjoin(rtn, segment);
	free(temp);
	free(segment);
	return rtn;
}

char **del_quote(char *word) {
	int dquote = 0;
	int squote = 0;
	int i = 0;
	int start = 0;
	char *rtn = xstrndup("", 0);
	char **expanded_tokens = NULL;

	while (word[i]) {
		if (word[i] == '"' && squote == 0) {
			if (dquote == 1 || (dquote == 0 && (start != i)))
				rtn = append_segment(rtn, word, start, i);
			dquote = !dquote;
			start = i + 1;
			i++;
		} else if (word[i] == '\'' && dquote == 0) {
			if (squote == 1 || (squote == 0 && (start != i)))
				rtn = append_segment(rtn, word, start, i);
			squote = !squote;
			start = i + 1;
			i++;
		} else if (!(dquote == 0 && squote == 1) && word[i] == '$') {
			rtn = append_segment(rtn, word, start, i);
			int temp_i = i;
			char *expanded = expander(word, &temp_i);
			char *temp = rtn;
			rtn = ft_strjoin(rtn, expanded);
			free(temp);
			free(expanded);
			i = temp_i;
			start = i;
		} else {
			i++;
		}
	}
	if (start < i)
		rtn = append_segment(rtn, word, start, i);

	if (contains_wildcard(word)) {
		expanded_tokens = expand_wildcard(rtn);
		free(rtn);
	} else {
		expanded_tokens = malloc(sizeof(char *) * 2);
		expanded_tokens[0] = rtn;
		expanded_tokens[1] = NULL;
	}

	return expanded_tokens;
}

// char *del_quote(char *word)
// {
//	 int dquote = 0;
//	 int squote = 0;
//	 int i = 0;
//	 int start = 0;
//	 char *rtn = xstrndup("", 0);
//	 while (word[i])
//	 {
//		 if (word[i] == '"' && squote == 0)
//		 {
//			 if (dquote == 1 || (dquote == 0 && (start != i)))
//				 rtn = append_segment(rtn, word, start, i);
//			 dquote = !dquote;
//			 start = i + 1;
//			 i++;
//		 }
//		 else if (word[i] == '\'' && dquote == 0)
//		 {
//			 if (squote == 1 || (squote == 0 && (start != i)))
//				 rtn = append_segment(rtn, word, start, i);
//			 squote = !squote;
//			 start = i + 1;
//			 i++;
//		 }
//		 else if (!(dquote == 0 && squote == 1) && word[i] == '$')
//		 {
//			 rtn = append_segment(rtn, word, start, i);
//			 int temp_i = i;
//			 char *expanded = expander(word, &temp_i);
//			 char *temp = rtn;
//			 rtn = ft_strjoin(rtn, expanded);
//			 free(temp);
//			 free(expanded);
//			 i = temp_i;
//			 start = i;
//		 }
//		 else
//			 i++;
//	 }
//	 if (start < i)
//		 rtn = append_segment(rtn, word, start, i);
//	 if(contains_wildcard(word))
//	 {
//		 char *glob_expanded = expand_wildcard(rtn);
//		 free(rtn);
//		 rtn = glob_expanded;
//	 }
//	 return rtn;
// }

char *expander(const char *word, int *index, t_config config)
{
	char *result = NULL;

	if (!word || word[*index] != '$')
		return NULL;
	int i = *index + 1;
	if (word[i] == '?')
	{
		char status[12];
		*index = i + 1;

		return itoa(config.exit_status);
	}
	else 
	{
		int start = i;
		while (word[i]) {
			if (!ft_isalnum(word[i]) && word[i] != '_') {
				*index = i;
				return xstrndup("", 0);
			}
			i++;
		}
		char *name = xstrndup(&word[start], i - start);
		//envが変わる場合にここを対応する必要がある
		char *value = getenv(name);
		free(name);
		if (value)
			result = xstrndup(value, strlen(value));
		else
			result = xstrndup("", 0);
		*index = i;
		return result;
	}
	return NULL;
}

