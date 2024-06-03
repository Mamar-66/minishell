/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:03:21 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/24 17:30:37 by omfelk           ###   ########.fr       */
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
			env->env[i] = ft_strdup(pwd);
		}
		else if (ft_strncmp(env->env[i], oldpwd, 8) == 0)
		{
			free(env->env[i]);
			env->env[i] = ft_strdup(oldpwd);
		}
		i++;
	}
}

char	*ft_cdd(char *str, char **argv, t_data *env)
{
	char	*path;
	int		i;

	if (!ft_strncmp(str, "-", 2))
	{
		i = -1;
		while (env->tenv[++i])
		{
			if (ft_strncmp(env->tenv[i], "OLDPWD=", 7) == 0)
			{
				path = env->tenv[i] + 7;
				if (!env->is_pipe)
					printf("%s\n", path);
				else
					write_in_stdin(path, false, env);
			}
		}
		if (!path)
		{
			fre(argv);
			env->status = 1;
			if (env->is_pipe)
				write_in_stdin("", true, env);
			printf("mishelle: cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		path = str;
	return (path);
}
