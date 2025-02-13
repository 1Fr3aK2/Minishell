#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../includes/shellinho.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	is_quote(char c)
{
	return ((c == '\'' || c == '\"'));
}

static int count_word(char *str)
{
    int i = 0;
    int words = 0;
    int in_word = 0;
    int in_quotes = 0;
    char quote_type = 0; // Guarda se estamos em aspas simples ou duplas

    if (!str)
        return -1;

    while (str[i])
    {
        if (is_quote(str[i]))
        {
            if (in_quotes && str[i] == quote_type) // Fechando aspas
                in_quotes = 0;
            else if (!in_quotes) // Abrindo aspas
            {
                in_quotes = 1;
                quote_type = str[i]; // Guarda qual aspas foi usada
                words++; // Conta o conteúdo entre aspas como uma única palavra
            }
            i++;
            continue;
        }

        if (!is_space(str[i]) || in_quotes) // Se não for espaço OU estiver dentro de aspas
        {
            if (!in_word && !in_quotes) // Só conta palavras fora das aspas
            {
                words++;
                in_word = 1;
            }
        }
        else
            in_word = 0; // Saiu de uma palavra

        i++;
    }

    return words;
}

int main(int argc, char *argv[])
{
	int i = 1;
	int j = 0;
	while(argv[i])
	{
		printf("%s\n", argv[i]);
		j += count_word(argv[i]);
		i++;
	}
	printf("%d\n", j);
}

// static char	*word_aloc(const char *str)
// {
// 	char	*word;
// 	int		word_len;
// 	int		i;

// 	if (!str)
// 		return (NULL);
// 	i = -1;
// 	word_len = 0;
// 	while (str[word_len] && !is_space(str[word_len]))
// 		word_len++;
// 	word = (char *)malloc(word_len + 1);
// 	if (!word)
// 		return (NULL);
// 	while (++i < word_len)
// 		word[i] = str[i];
// 	word[i] = '\0';
// 	return (word);
// }

// static void	*free_str(char **dest, int i)
// {
// 	while (i >= 0)
// 		free(dest[i--]);
// 	free(dest);
// 	return (NULL);
// }

// char	**custome_ft_split(char *s)
// {
// 	char	**dest;
// 	int		i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	dest = (char **)malloc((count_word(s) + 1) * sizeof(char *));
// 	if (!dest)
// 		return (NULL);
// 	while (*s)
// 	{
// 		while (*s && is_space(*s))
// 			s++;
// 		if (*s)
// 		{
// 			dest[i] = word_aloc(s);
// 			if (!dest[i++])
// 				return (free_str(dest, i - 1), NULL);
// 		}
// 		while (*s && !is_space(*s))
// 			s++;
// 	}
// 	dest[i] = 0;
// 	return (dest);
// }

// int main() {
//     char *input = "hello 'this is a test' world";
// 	printf("initial string : %s\n\n", input);
//     char **split_output = custome_ft_split(input);
//     if (!split_output) {
//         printf("Error allocating memory\n");
//         return 1;
//     }
//     printf("Splitting input using custome_ft_split:\n");
//     for (int i = 0; split_output[i]; i++) {
//         printf("Word: %s\n", split_output[i]);
//         free(split_output[i]);
//     }
//     free(split_output);
//     return 0;
// }