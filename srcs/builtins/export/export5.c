/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:33:59 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/13 13:34:01 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	delete(int i, t_data *env)
{
	free(env->tenv[i]);
	while (env->tenv[i])
	{
		env->tenv[i] = env->tenv[i + 1];
		i++;
	}
}

static char	*deletes(char *str, char *env)
{
	int		j;
	int		a;
	size_t	i;
	char	*res;

	res = ft_calloc(sizeof(char), ft_strlen(env) + 1);
	j = 0;
	a = 0;
	while (env[j])
	{
		i = 0;
		if (j != 0 && env[j - 1] == ' ')
			while (str[i] == env[j + i] && str[i] && env[j + i])
				i++;
		else if (j == 0)
			while (str[i] == env[j + i] && str[i] && env[j + i])
				i++;
		if (i == ft_strlen(str) && (env[i + j] == ' ' || env[i + j] == '\0'))
		{
			printf("minishelle: export: `%s\': not a valid identifier\n", str);
			j = j + i;
		}
		res[a++] = env[j++];
	}
	return (res);
}

void	ft_unsetbis(char *str, t_data *env)
{
	int		i;
	int		j;
	char	**argv;

	argv = ft_split(str, ' ');
	j = 0;
	while (argv[j])
	{
		i = 0;
		while (env->tenv[i])
		{
			if (ft_stcmp(argv[j], env->tenv[i], ft_strlen(argv[j])) == 0)
			{
				printf("minishelle: export: `%s\': not a valid identifier\n",
					env->tenv[i]);
				delete(i, env);
			}
			i++;
		}
		env->t = deletes(argv[j], env->t);
		j++;
	}
	fre(argv);
}

void	metacarac(char *str, t_data *env)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= 33 && str[i] <= 47) || (str[i] >= 58
				&& str[i] <= 64 && str[i] != '=') || (str[i] >= 91
				&& str[i] <= 96 && str[i] != 95)
			|| (str[i] >= 123 && str[i] <= 126))
		{
			ft_unsetbis(str, env);
			return ;
		}
		i++;
	}
}

char	*verif(char *a)
{
	size_t	i;
	char	*b;

	b = ft_calloc(sizeof(char), ft_strlen(a) + 1);
	i = 0;
	while (i != ft_strlen(a))
	{
		while (a[i] == ' ' && i != ft_strlen(a))
			i++;
		if ((a[i] <= 90 && a[i] >= 65)
			|| (a[i] <= 122 && a[i] >= 97) || (a[i] == ' '))
		{
			while (a[i] != ' ' && i != ft_strlen(a))
				i++;
		}
		else if (a[i])
		{
			b = veriff(a, b, i);
			return (b);
		}
		if (i != ft_strlen(a))
			i++;
	}
	b[0] = 'a';
	return (b);
}