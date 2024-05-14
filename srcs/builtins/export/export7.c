/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:34:12 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/13 13:34:14 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	notgood(char *str, t_data *env)
{
	int	i;

	i = 0;
	while (env->tenv[i])
	{
		if (ft_strncmp(str, env->tenv[i], ftn(str)) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	extension(char **av, t_data *env, int i, int j)
{
	char	*temp;

	temp = ft_calloc(sizeof(char), 1);
	temp = av[i + j];
	av[j] = copy(av[j]);
	ft_unset(av[j], env);
	env->t[ft_strlen(env->t)] = ' ';
	env->t = ft_strjoin(env->t, temp);
}

void	extensiontwo(char **av, t_data *env, int i, int j)
{
	char	*temp;

	temp = ft_calloc(sizeof(char), 1);
	temp = av[j];
	av[j + i] = copy(av[j + i]);
	ft_unset(av[j + i], env);
	env->t[ft_strlen(env->t)] = ' ';
	env->t = ft_strjoin(env->t, temp);
}
