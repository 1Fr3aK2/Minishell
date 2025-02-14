#include "../../includes/shellinho.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	count_word(char *str)
{
	int		i;
    int     words;
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
			if (str[i] == quote) // Fechou aspas
				i++;
		}
		else
			while (str[i] && !is_space(str[i]) && !is_quote(str[i]))
				i++;
		words++;
	}
	return (words);
}
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
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

char	**custome_ft_split(char *s)
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

int	main(int argc, char **argv)
{
	char	**teste;
	char	*str;
	int		i;

	str = "   \"asdas \"\"asdasd\" dasdasd1\"   654  \"        \"    rafaada s \" asdasd     ''    asdasd\" asd";
	teste = custome_ft_split(str);
	i = 0;
	while (teste[i])
	{
		printf("teste[%d] = %s\n", i, teste[i]);
		i++;
	}
}
