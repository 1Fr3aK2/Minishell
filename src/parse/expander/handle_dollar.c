#include "../../../includes/shellinho.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

static int	process_variable(char *str, char **env, char **new, int i)
{
	char	*var_name;
	char	*var_value;
	char	*temp;

	var_name = expand(str + i);
	if (!var_name)
		return (i + 1);
	var_value = translate(var_name, env);
	if (var_value)
	{
		temp = join_and_free(*new, var_value);
		if (!temp)
		{
			free(*new);
			return (-1);
		}
		*new = temp;
	}
	return (i + get_varname_len(str + i) + 1);
}

char	*handle_dollar(char *str, char **env)
{
	char	*new;
	char	*temp;
	int		i;

	if (check_translate(str) == 0)
		return (NULL);
	new = ft_strdup("");
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		temp = ft_substr(str, i, size_to_var(str + i));
		if (!temp)
			return (free(new), NULL);
		new = join_and_free(new, temp);
		if (!new)
			return (free(temp), NULL);
		free(temp);
		i += size_to_var(str + i);
		if (str[i] == '$')
			i = process_variable(str, env, &new, i);
	}
	return (new);
}
