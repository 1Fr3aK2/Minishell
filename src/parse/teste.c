CORRIGIR TESTES


echo "O meu user é $USER e estou em $PWD" -> correto : O meu user é rafael e estou em /home/rafael
echo "$HOME$USER" -> correto : /home/rafaelrafael
echo "$HOME$NAO_EXISTE" -> correto : /home/rafael
echo "User: $USER, Desconhecido: $NAO_EXISTE" -> correto : User: rafael, Desconhecido:

echo $123ABC -> bash -> 23ABC
            -> zsh -> zsh: command not found: 23ABC
            outros(nos) -> \n 

echo $HOME!USER -> bash -> bash: !USER: event not found
                -> ZSH -> zsh: event not found: USER
                outros(nos) -> /home/rafael!USER


echo "'$HOME'" -> correto -> '/home/rafael'
echo "asd"'$HOME'"asd" -> asd$HOMEasd
 echo "Inicio"'$PWD'"Fim" -> Inicio$PWDFim





 static char	*handle_dollar(char *str, char **env)
 {
     char	*teste;
     char	*final;
     char	*new;
     int		len;
     char	*temp;
 
     if (check_translate(str) == 0)
         return (NULL);
     new = ft_strdup("");
     while (*str)
     {
         temp = ft_substr(str, 0, size_to_var(str));
         teste = expand(str);
         final = translate(teste, env);
         new = ft_strjoin(new, temp);
         if (final) 
             new = ft_strjoin(new, final);
         len = size_to_var(str) + get_varname_len(str) + 1;
         str += len;
     }
     return (new);
 }

 static char *handle_dollar(char *str, char **env)
{
    char *var_name;
    char *var_value;
    char *new;
    int len;
    char *temp;
	char *new_temp;
    int i = 0;
	char *new_value;

    if (check_translate(str) == 0)
        return (NULL);
    new = ft_strdup("");
    if (!new)
        return NULL;
		while (str[i])
		{
			len = size_to_var(str + i);
			temp = ft_substr(str, i, len);
			new_temp = ft_strjoin(new, temp);
			/* free(new);
			free(temp); */
			new = new_temp;
	
			i += len;
			if (str[i] == '$')
			{
				var_name = expand(str + i);
				if (var_name)
				{
					var_value = translate(var_name, env);
				   /*  free(var_name); */
					if (var_value)
					{
						new_value = ft_strjoin(new, var_value);
						/* free(new);
						free(var_value); */
						new = new_value;
					}
					i += get_varname_len(str + i) + 1; // +1 para o '$'
				}
				else
				{
					i++; // Avança pelo '$' se não houver expansão
				}
			}
		}
		return new;
}