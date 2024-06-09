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

void	deletebis(int i, t_data *env)
{
	free(env->tenv[i]);
	while (env->tenv[i])
	{
		env->tenv[i] = env->tenv[i + 1];
		i++;
	}
}

char	*deletesbis(char *str, char *env, int j, t_data *en)
{
	int		a;
	int		z;
	size_t	i;
	char	*res;

	res = ft_calloc(sizeof(char), ft_strlen(env) + 2);
	j = 0;
	a = 0;
	z = 0;
	while (env[j])
	{
		i = 0;
		if (j != 0 && env[j - 1] == ' ')
			while (str[i] == env[j + i] && str[i] && env[j + i])
				i++;
		else if (j == 0)
			while (str[i] == env[j + i] && str[i] && env[j + i])
				i++;
		if (i == ft_strlen(str) && (env[i + j] == ' ' || env[i + j] == '\0') && z == 0)
		{
			ft_error_and_status(en, str);
			z++;
		}
		if (i == ft_strlen(str) && (env[i + j] == ' ' || env[i + j] == '\0'))
			j = j + i;
		res[a++] = env[j++];
	}
	free(env);
	free(en->t);
	return (res);
}

char	*changeles(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j + i])
	{
		while (str[j + i] == c)
			i++;
		if (str[i + j])
		{
			str[j] = str[j + i];
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}

void	ft_unsetbis(char *str, t_data *env)
{
	int		i;
	int		j;
	char	*t;

	j = 0;
	if (no_quote(str) == 0)
		str = changeles(str, '"');
	else
		str = changeles(str, '\'');
	if (str)
	{
		i = 0;
		while (env->tenv[i])
		{
			if (ft_stcmp(str, env->tenv[i], ft_strlen(str)) == 0)
				deletebis(i, env);
			i++;
		}
		t = ft_calloc(sizeof(char), ft_strlen(env->t) + 5);
		ft_strlcpy(t, env->t, INT_MAX);
		env->t = deletes_for_no_mess(str, t, j, env);
	}
}

void	metacarac(char *str, t_data *env, char *t)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= 32 && str[i] <= 47) || (str[i] >= 58
				&& str[i] <= 64 && str[i] != '=') || (str[i] >= 91
				&& str[i] <= 96 && str[i] != 95)
			|| (str[i] >= 123 && str[i] <= 126))
		{
			ft_unsetbisbis(str, env, t);
			return ;
		}
		i++;
	}
	i = 0;
	if (str[i] && (!(str[i] <= 90 && str[i] >= 65)
			&& !(str[i] <= 122 && str[i] >= 97) && str[i] != '_'))
	{
		ft_unsetbisbis(str, env, t);
	}
}
