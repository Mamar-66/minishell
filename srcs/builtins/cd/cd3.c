/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:16:12 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/10 12:16:13 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	less_line(char **argv, t_data *env)
{
	fre(argv);
	env->status = 1;
	if (env->is_pipe)
		write_in_stdin("", true, env);
	printf("mishell: cd: too many arguments\n");
}

char	*dollars_parsing_bis(char *str, t_data *env)
{
	int		i;
	int		a;
	int		z;

	i = 0;
	a = 0;
	z = 0;
	env->dolar = 1;
	if (check_dollar_position(str) != 5)
	{
		str = dollars_parsing_suite(str, z, env);
	}
	str = parsing_export(str, env);
	return (str);
}

char	*no_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i + j])
	{
		if (str[0] == ' ' && str[i + j] == ' ' && j == 0)
		{
			while (str[i + j] && str[i + j] == ' ')
				j++;
			while (str[i + j] && str[i + j] != ' ')
				j++;
		}
		else if (j == 0)
			while (str[i + j] && str[i + j] != ' ')
				j++;
		str[i] = str[i + j];
		if (str[j + i])
			i++;
	}
	str[i] = '\0';
	return (str);
}

char	*oldpwd_cd(t_data *env, int i, char *str, char *path)
{
	if (ft_strncmp(env->tenv[i], "OLDPWD=", 7) == 0)
	{
		free(str);
		path = ft_strdup(env->tenv[i] + 7);
		if (!env->is_pipe)
			printf("%s\n", path);
		else
			write_in_stdin(path, false, env);
	}
	return (path);
}
