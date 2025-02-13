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

// Conta quantas palavras existem na string,considerando espaços e aspas corretamente
static int	count_word(char *str)
{
	int		i;
    int     words;
	char	quote;

	i = 0;
    words = 0;
	quote = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		while (is_space(str[i])) // Ignorar espaços
			i++;
		if (!str[i])
			break ;
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote) // Fechou aspas
				i++;
		}
		else
		{
			while (str[i] && !is_space(str[i]) && !is_quote(str[i]))
				i++;
		}
		words++;
	}
	return (words);
}

// Aloca memória e extrai a próxima palavra considerando aspas corretamente
static char	*word_aloc(char **str)
{
	char	*word;
	int		start;
    int     end;
	char	quote;
	int		i;

	start = 0;
    end = 0;
	quote = 0;
	// Se começar com aspas, encontrar a aspa correspondente
	if (is_quote((*str)[start]))
	{
		quote = (*str)[start]; // Captura a aspa inicial
		end++;
		while ((*str)[end] && (*str)[end] != quote)
			end++;
		if ((*str)[end] == quote) // Se encontrar a aspa de fechamento
			end++;
	}
	else
	{
		while ((*str)[end] && !is_space((*str)[end]))
			end++;
	}
	// Alocar memória para a palavra e copiar os caracteres, incluindo as aspas
	word = (char *)malloc(end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i++] = (*str)[start++];
	}
	word[i] = '\0';
	*str += end; // Avançar o ponteiro da string original para o próximo token
	return (word);
}

static void	*free_str(char **dest, int i)
{
	while (i >= 0)
		free(dest[i--]);
	free(dest);
	return (NULL);
}

// Função principal que divide a string em palavras corretamente
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

	str = "      654  \"        \"    rafaada s \" asdasd     ''    asdasd\" asd";
	teste = custome_ft_split(str);
	i = 0;
	while (teste[i])
	{
		printf("teste[%d] = %s\n", i, teste[i]);
		i++;
	}
}
