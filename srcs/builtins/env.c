/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:21 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/05 12:18:14 by omfelk           ###   ########.fr       */
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

void	ft_exportation(char *argv, t_data *env, int k)
{
	char	**trier;
	char	**temp;
	char	*t;
	int		j;

	t = NULL;
	while (--k != 0)
	{
		j = 0;
		if (env->t)
		{
			temp = ft_calloc(sizeof(char *), (ft_export_count(t, env, j) + 2));
			temp = ft_export_temp(t, env, temp, j);
		}
		else
			temp = ft_calloc(sizeof(char *), 2);
		nodouble(temp, env);
		trier = plus(temp, env);
		changeenv(trier, env);
		nodouble(temp, env);
		if (v(argv + 6) == 0)
			fre(trier);
		fre(temp);
	}
}

void	env_suite(t_data *en, int i)
{
	if (!en->exit_f.str_reel[1])
		ft_exportation("export", en, 3);
	while (en->env[++i])
		printf("%s\n", en->env[i]);
}

void	ft_env(char *str, t_data *en)
{
	int		i;
	char	**temp;
	char	*rev;

	temp = ft_split(str, ' ');
	if (certif(temp, en) == 0)
	{
		if (en->is_pipe)
			write_in_stdin("", true, en);
		return ;
	}
	i = -1;
	if (en->env)
	{
		if (!en->is_pipe)
			env_suite(en, i);
		else
		{
			rev = inverse_split(en->env);
			write_in_stdin(rev, true, en);
			free(rev);
		}
	}
}
