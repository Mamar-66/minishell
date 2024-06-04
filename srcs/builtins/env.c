/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:21 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/04 17:21:32 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	certif(char **argv, t_data *env)
{
	int	i;

	if (argv[1])
	{
		env->status = 127;
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
	char	*rev;

	printf("bool env = %d\n", en->is_pipe);
	temp = ft_split(str, ' ');
	if (certif(temp, en) == 0)
	{
		if (en->is_pipe)
			write_in_stdin("", true, en);
		return ;
	}
	i = -1;
	ft_exportation("export", en);
	if (en->env)
	{
		if (!en->is_pipe)
			while (en->env[++i])
				printf("%s\n", en->env[i]);
		else
		{
			rev = inverse_split(en->env);
			write_in_stdin(rev, true, en);
			free(rev);
		}
	}
}
