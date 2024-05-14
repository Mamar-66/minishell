/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:21 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/26 15:56:24 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	certif(char **argv)
{
	int	i;

	if (argv[1])
	{
		printf("NoNoNo\n");
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

void	ft_env(char *str, t_data *en)
{
	int		i;
	char	**temp;

	temp = ft_split(str, ' ');
	if (certif(temp) == 0)
		return ;
	i = 0;
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
