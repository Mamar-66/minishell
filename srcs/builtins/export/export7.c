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

char	*encoress(char *temp, char **argv)
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
	free(temp);
	return (res);
}

void	extension(char **av, t_data *env, int i, int j)
{
	char	*temp;

	temp = av[i + j];
	av[j] = copy(av[j]);
	ft_unset(av[j], env);
	env->t[ft_strlen(env->t)] = ' ';
	env->t = ft_strjoin(env->t, temp);
}

void	extensiontwo(char **av, t_data *env, int i, int j)
{
	char	*temp;

	temp = av[j];
	av[j + i] = copy(av[j + i]);
	ft_unset(av[j + i], env);
	env->t[ft_strlen(env->t)] = ' ';
	env->t = ft_strjoin(env->t, temp);
}

int	suiteverif(size_t i, char *a)
{
	while (a[i] == ' ' && i != ft_strlen(a))
		i++;
	return (i);
}
