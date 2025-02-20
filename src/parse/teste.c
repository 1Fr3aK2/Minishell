#include "../../includes/shellinho.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
char	*ft_strchr(const char *str, int c)
{
	char	*s;

	if (!str)
		return (NULL);
	s = (char *)str;
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return (s);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*get_env(char *variable_name, char **env)
{
	int		i;
	int		len;
	char	*value;

	if (!variable_name || !env || !*env)
		return (NULL);
	i = 0;
	len = ft_strlen(variable_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], variable_name, len) == 0 && env[i][len] == '=')
		{
			value = ft_strchr(env[i], '=');
			if (!value)
				return (NULL);
			else
				return (value + 1);
		}
		i++;
	}
	return (NULL);
}

char *handle_dollar(char *str, char **env)
{
	int i = 0;
	char *teste;
	while(str)
	{
		if (str[i] && str[i] == '$')
		{
			teste = get_env(&str[++i],env);
			return(teste);
		}
        i++;
	}
	return (NULL);	
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 2)
    {
        printf("Usage: %s \"$VARIABLE\"\n", argv[0]);
        return (1);
    }
    
    char *result = handle_dollar(argv[1], envp);
    if (result)
        printf("Resolved value: %s\n", result);
    else
        printf("Variable not found or invalid input.\n");
    return (0);
}
