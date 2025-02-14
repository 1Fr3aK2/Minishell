#include "../../includes/shellinho.h"

int	count_quotes(char *input)
{
	int	quotes;
	int	i;

	if (!input)
		return (0);
	i = 0;
	quotes = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
			quotes++;
		i++;
	}
	return (quotes);
}

int	count_word(char *str)
{
	int		i;
	int		words;
	char	quote;

	i = 0;
	words = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				i++;
		}
		else
			while (str[i] && !is_space(str[i]) && !is_quote(str[i]))
				i++;
		words++;
	}
	return (words);
}

static char	*word_aloc(char **str)
{
	char	*word;
	int		start;
	char	quote;

	start = 0;
	quote = 0;
	if (is_quote((*str)[start]))
	{
		quote = (*str)[start];
		while ((*str)[++start] && (*str)[start] != quote)
			;
		if ((*str)[start] == quote)
			start++;
	}
	else
		while ((*str)[start] && !is_space((*str)[start]))
			start++;
	word = (char *)malloc(sizeof(char) * (start + 1));
	if (!word)
		return (NULL);
	ft_strncpy(word, *str, start);
	word[start] = '\0';
	*str += start;
	return (word);
}

static void	*free_str(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
	return (NULL);
}

char	**ft_split_quotes(char *s)
{
	char	**dest;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char **)malloc((count_word(s) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (*s)
	{
		while (*s && is_space(*s))
			s++;
		if (*s)
		{
			dest[i] = word_aloc(&s);
			if (!dest[i++])
				return (free_str(dest, i - 1));
		}
	}
	dest[i] = NULL;
	return (dest);
}
