/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export14.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:45:48 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 11:45:50 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*dollars_parsing_suite(char *str, int z, t_data *env)
{
	int		i;
	int		a;
	char	*t;
	char	*temp;

	while (dolar(str) == 0)
	{
		t = ft_calloc(sizeof(char), ft_strlen(str) + 100);
		i = 0;
		a = 0;
		while (str[i + a] != '$')
		{
			t[i] = str[i + a];
			i++;
			if (str[i + a] == '$')
				z = i + a;
		}
		t = ft_strjoin_two_free(t, val_var(str + z + 1, &z, env));
		temp = str;
		str = ft_strjoin(t, str + z + 1);
		if (dolar(str) != 0 && env->dolar == 0)
			free(temp);
		env->dolar = 0;
	}
	return (str);
}

char	*flemme(char **argv, int i, int j, int c)
{
	int	a;

	a = 0;
	while (argv[i] && argv[i][j + c])
	{
		while (argv[i][j + c] && argv[i][j + c] == '"')
		{
			argv[i][j] = argv[i][j + c];
			a++;
			j++;
		}
		while (argv[i][j + c] && argv[i][j + c] == '\'' && a % 2 != 1)
			c++;
		argv[i][j] = argv[i][j + c];
		if (argv[i][j + c])
			j++;
	}
	argv[i][j] = '\0';
	return (argv[i]);
}

char	*flemme_bis(char **argv, int i, int j, int c)
{
	int	a;

	a = 0;
	while (argv[i] && argv[i][j + c])
	{
		while (argv[i][j + c] && argv[i][j + c] == '\'')
		{
			argv[i][j] = argv[i][j + c];
			a++;
			j++;
		}
		while (argv[i][j + c] && argv[i][j + c] == '"' && a % 2 != 1)
			c++;
		argv[i][j] = argv[i][j + c];
		if (argv[i][j + c])
			j++;
	}
	argv[i][j] = '\0';
	return (argv[i]);
}

char	**ft_export_temp(char *t, t_data *env, char **temp, int j)
{
	(void)t;
	temp[j] = recover_word(env->t, 1 + j, false);
	while (temp[j])
	{
		j++;
		temp[j] = recover_word(env->t, 1 + j, false);
	}
	return (temp);
}

int	ft_export_count(char *t, t_data *env, int j)
{
	t = recover_word(env->t, 1 + j, false);
	while (t)
	{
		free(t);
		j++;
		t = recover_word(env->t, 1 + j, false);
	}
	free(t);
	return (j);
}
