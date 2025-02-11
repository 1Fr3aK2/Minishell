#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_quote(char c)
{
    return (c == '\'' || c == '\"');
}

bool is_space(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

int count_skip_quotes(char *input)
{
    int quotes = 0;
    int i = 0;

    if (!input)
        return 0;
    
    while (input[i])
    {
        while (is_space(input[i]))
            i++;
        
        if (is_quote(input[i]))
        {
            i++;
            quotes++;
        }
        i++;
    }
    return quotes;
}
size_t	ft_strlen(const char *str)
{
	size_t	length;

	if (!str)
		return (-1);
	length = 0;
	while (str[length])
		length++;
	return (length);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str_copied;

	if (!s || start < 0 || len <= 0)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (start + len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	str_copied = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str_copied)
		return (NULL);
	while (i < len && s[i])
	{
		str_copied[i] = s[start + i];
		i++;
	}
	str_copied[i] = '\0';
	return (str_copied);
}

static char *new_input(char *input)
{
    int i;
	char *new = NULL;
    int len;
    int j;

	// new = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	// if (!new)
	// 	return (NULL);
    i = 0;
    printf("initial input =\n %s", input);
	if (count_skip_quotes(input) % 2 != 0)
	{
		printf("ERROR\n");
		return (NULL);
	}
	len = ft_strlen(input);
	while(!(is_quote(input[i])))
		i++;
	j = i + 1;
    // printf("%d\n", i);   
	new = ft_substr(input, j, (len - j - 1));
	if (!new)
		return (input);
	else
        printf("estou aqui adsd%s\n", new);
    return (new);		
}

int main()
{
    char *str = "asdasdasdasdasD";
    char *e = new_input(str);
    
    if (e)
        printf("%s\n", e);
    else
        printf("Erro ao processar a string\n");

    free(e);  // Libera a memória alocada

    return 0;
}
