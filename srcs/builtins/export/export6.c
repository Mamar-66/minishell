/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:34:06 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/13 13:34:07 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	changeenv(char **av, t_data *ev)
{
	int	i;
	int	a;

	if (ev->env)
		fre(ev->env);
	i = 0;
	while (av[i])
		i++;
	ev->env = ft_calloc(sizeof(char *), i + 3);
	i = -1;
	a = 0;
	while (av[++i + a])
	{
		if (findn(av[i + a]) != 0)
		{
			if (av[i + a][0] == '"')
				ev->env[i] = ft_strdup(av[i + a] + 1);
			if (av[i + a][0] == '"')
				ft_strlcpy(ev->env[i], ev->env[i], ft_strlen(ev->env[i]) - 1);
			else
				ev->env[i] = ft_strdup(av[i + a]);
		}
		else
			a++;
	}
}

char	*copy(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

int	ftn(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	nodouble(char **av, t_data *env)
{
	int		i;
	int		j;

	j = 0;
	while (av[j])
	{
		i = 1;
		while (av[i + j])
		{
			if (notgood(av[j + i], env) == 0)
				i = i + 1 - 1;
			else if (ft_scmp(av[j], av[i + j], ftn(av[j])) == 0
				|| ft_scmp_bis(av[j], av[i + j], ftn(av[j])) == 0)
			{
				if (findn(av[j + i]) == 0)
					extensiontwo(av, env, i, j);
				else
					extension(av, env, i, j);
			}
			i++;
		}
		j++;
	}
}

char	**decale(char **argv, int i)
{
	int	j;

	j = 0;
	free(argv[i]);
	while (argv[i + j])
	{	
		argv[i + j] = argv[i + 1 + j];
		j++;
	}
	return (argv);
}
