/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:32 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/26 15:56:34 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*encore(char **argv, char *temp)
{
	int		i;
	char	*res;

	i = 0;
	while (temp[i])
		i++;
	res = ft_calloc(sizeof(char), i + 10);
	i = 0;
	res[0] = '5';
	while (argv[i])
	{
		if (findn(temp) == findn(argv[i]))
			if (ft_strncmp(argv[i], temp, findn(argv[i])) == 0)
				return (res);
		i++;
	}
	i = 0;
	while (temp[i])
	{
		res[i] = temp[i];
		i++;
	}
	return (res);
}

char	*encores(char *temp, char **argv)
{
	int		i;
	char	*res;

	i = 0;
	while (argv[i])
	{
		if (findn(temp) == findn(argv[i]))
		{
			if (ft_strncmp(argv[i], temp, findn(argv[i])) == 0)
				temp = argv[i];
		}
		else if (ft_strncmp(argv[i], temp, ft_strlen(argv[i])) == 0)
			argv = decale(argv, i);
		i++;
	}
	i = 0;
	while (temp[i])
		i++;
	res = ft_calloc(sizeof(char), i + 10);
	i = -1;
	while (temp[++i])
		res[i] = temp[i];
	return (res);
}

char	**plus(char **temp, t_data *env)
{
	int		i;
	int		j;
	char	**trier;

	i = 0;
	j = 0;
	while (env->tenv[i])
		i++;
	while (temp[j])
		j++;
	trier = ft_calloc(sizeof(char *), i + j + 3);
	i = 0;
	while (env->tenv[i])
	{
		trier[i] = encores(env->tenv[i], temp);
		env->tenv[i] = encoress(env->tenv[i], temp);
		i++;
	}
	j = -1;
	while (temp[++j])
	{
		trier[i + j] = encore(env->tenv, temp[j]);
	}
	return (trier);
}

char	**trie(char **trier)
{
	int		i;
	char	**temp;

	temp = ft_calloc(sizeof(char *), 2);
	while (good(trier) != 0)
	{
		i = 0;
		trier = trie2(trier, temp, i);
	}
	free(temp);
	return (trier);
}

void	ft_export(char *argv, t_data *env, char *str)
{
	char	**trier;
	char	**temp;
	char	*t;
	int		i;

	t = NULL;
	str = dollars_parsing(no_space(str), env);
	str = parsing_export(str, env);
	if (v(argv + 6) != 0)
		ft_export_strjoin(env, str);
	env->t = modify_string(env->t, str);
	temp = ft_calloc(sizeof(char *), (ft_export_count(t, env, 0) + 5));
	temp = ft_export_temp(t, env, temp, 0);
	i = -1;
	nodouble(temp, env);
	while (temp[++i])
		export_metacarac(temp, i, t, env);
	trier = plus(temp, env);
	changeenv(trier, env);
	nodouble(temp, env);
	if (v(argv + 6) == 0)
		trie_print_ajoute(temp, trier, env);
	else
		is_pipe_export(env, trier, temp);
	fre(temp);
}
