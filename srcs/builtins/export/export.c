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
	trier = ft_calloc(sizeof(char *), i + j + 1);
	i = 0;
	while (env->tenv[i])
	{
		trier[i] = encores(env->tenv[i], temp);
		env->tenv[i] = encores(env->tenv[i], temp);
		i++;
	}
	j = -1;
	while (temp[++j])
		trier[i + j] = encore(env->tenv, temp[j]);
	fre(temp);
	return (trier);
}

char	**trie(char **trier)
{
	int		i;
	char	**temp;

	temp = ft_calloc(sizeof(char *), 1);
	while (good(trier) != 0)
	{
		i = 0;
		trier = trie2(trier, temp, i);
	}
	free(temp);
	return (trier);
}

void	ft_export(char *argv, t_data *env)
{
	char	**trier;
	char	**temp;
	int		i;

	env->t = ft_stjoin(env->t, argv + 6);
	temp = ft_split(env->t, ' ');
	nodouble(env->t, env);
	ft_exportt(argv, env);
	i = 0;
	while (temp[i])
	{
		metacarac(temp[i], env);
		i++;
	}
	trier = plus(temp, env);
	changeenv(trier, env);
	if (v(argv + 6) == 0)
	{	
		temp = trie(trier);
		temp = ajoute(temp);
		print(temp);
		fre(trier);
	}
}
