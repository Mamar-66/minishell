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
	int		i;
	int		j;

	t = NULL;
	while (--k != 0)
	{
		env->t = modify_string(env->t);
		j = 0;
		temp = ft_calloc(sizeof(char *), (ft_export_count(t, env, j) + 5));
		temp = ft_export_temp(t, env, temp, j);
		i = -1;
		nodouble(temp, env);
		while (temp[++i])
			export_metacarac(temp, i, t, env);
		trier = plus(temp, env);
		changeenv(trier, env);
		if (v(argv + 6) == 0)
			fre(trier);
		else
			is_pipe_export(env, trier, temp);
	}
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
	ft_exportation("export", en, 2);
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
