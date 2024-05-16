/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:21 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/16 12:03:52 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	certif(char **argv)
{
	int	i;

	if (argv[1])
	{
		printf("minishelle: env: too many arguments\n");
		i = 0;
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
		return (0);
	}
	else
	{
		free(argv[0]);
		free(argv);
		return (1);
	}
}

void	ft_exportation(char *argv, t_data *env)
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
		fre(trier);
	}
	else
		fre(trier);
}

void	ft_env(char *str, t_data *en)
{
	int		i;
	char	**temp;

	temp = ft_split(str, ' ');
	if (certif(temp) == 0)
		return ;
	i = 0;
	ft_exportation("export", en);
	if (en->env)
	{
		while (en->env[i])
		{
			printf("%s\n", en->env[i]);
			i++;
		}
	}
	else
	{
		while (en->tenv[i])
		{
			printf("%s\n", en->tenv[i]);
			i++;
		}
	}
}
