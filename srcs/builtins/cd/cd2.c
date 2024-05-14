/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:03:21 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/13 14:03:24 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	changes(char *pwd, char *oldpwd, t_data *env)
{
	int	i;

	i = 0;
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], pwd, 5) == 0)
		{
			free(env->env[i]);
			env->env[i] = pwd;
		}
		else if (ft_strncmp(env->env[i], oldpwd, 8) == 0)
		{
			free(env->env[i]);
			env->env[i] = oldpwd;
		}
		i++;
	}
}

char	*ft_cdd(char **argv, t_data *env)
{
	char	*path;
	int		i;

	if (!ft_strncmp(argv[1], "-", 2))
	{
		i = 0;
		while (env->tenv[i])
		{
			if (ft_strncmp(env->tenv[i], "OLDPWD=", 7) == 0)
			{
				path = env->tenv[i] + 7;
				printf("%s\n", path);
			}
			i++;
		}
		if (!path)
		{
			fre(argv);
			printf("mishelle: cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		path = argv[1];
	return (path);
}
