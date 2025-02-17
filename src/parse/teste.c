#include "../../includes/shellinho.h"

bool	is_quote(char c)
{
	return ((c == '\'' || c == '\"'));
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

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

int count_word(char *str)
{
    int i = 0;
    int words = 0;
    char quote = 0;
    int in_quotes = 0;

    while (str[i])
    {
        while (str[i] && is_space(str[i]))
            i++;
        if (str[i])
        {
            words++;
            while (str[i] && (!is_space(str[i]) || in_quotes))
            {
                if (is_quote(str[i]))
                {
                    if (!in_quotes)
                    {
                        in_quotes = 1;
                        quote = str[i];
                    }
                    else if (str[i] == quote)
                    {
                        in_quotes = 0;
                    }
                }
                i++;
            }
        }
    }
    return words;
}

int main()
{
    char *test_strings[] = {
        "\"Hello world\"",
        "\"  Spaces   at   start and end  \"",
        "\"Quoted string\"",
        "Mixed \"quoted and\" unquoted",
        "\"Unclosed quote",
        "Multiple 'single' and \"double\" quotes",
        "Empty \"\" quotes",
        "\"Nested \"quotes\"\"",
        "",  // Empty string
        "One",
        "   ",  // Only spaces
        NULL
    };

    int i = 0;
    while (test_strings[i] != NULL)
    {
        int word_count = count_word(test_strings[i]);
        printf("String: \"%s\"\n", test_strings[i]);
        printf("Word count: %d\n\n", word_count);
        i++;
    }

    return 0;
}


/* static char	*word_aloc(char **str)
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
} */

// static void	*free_str(char **dest, int i)
// {
// 	while (i >= 0)
// 		free(dest[i--]);
// 	free(dest);
// 	return (NULL);
// }

char **ft_split_quotes(char *s)
{
    char **dest;
    int i, j, len;
    char quote;
    int in_quotes = 0;

    if (!s)
        return (NULL);

    dest = (char **)malloc((count_word(s) + 1) * sizeof(char *));
    if (!dest)
        return (NULL);

    i = 0;
    j = 0;
    while (s[i])
    {
        while (s[i] && is_space(s[i]))
            i++;
        if (s[i])
        {
            len = 0;
            quote = 0;
            in_quotes = 0;
            while (s[i + len] && (!is_space(s[i + len]) || in_quotes))
            {
                if (is_quote(s[i + len]))
                {
                    if (!in_quotes)
                    {
                        in_quotes = 1;
                        quote = s[i + len];
                    }
                    else if (s[i + len] == quote)
                    {
                        in_quotes = 0;
                    }
                }
                len++;
            }
            dest[j] = (char *)malloc(sizeof(char) * (len + 1));
            if (!dest[j])
                return (free_str(dest, j));
            strncpy(dest[j], s + i, len);
            dest[j][len] = '\0';
            j++;
            i += len;
        }
    }
    dest[j] = NULL;
    return (dest);
}

