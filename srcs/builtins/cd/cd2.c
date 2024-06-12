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

void	cd_erro(char **argv, t_data *env)
{
	fre(argv);
	env->status = 1;
	if (env->is_pipe)
		write_in_stdin("", true, env);
	printf("mishell: cd: OLDPWD not set\n");
}

char	*ft_cdd(char *str, char **argv, t_data *env)
{
	char	*path;
	int		i;

	path = NULL;
	if (!ft_strncmp(str, "-", 2))
	{
		i = -1;
		while (env->tenv[++i])
		{
			path = oldpwd_cd(env, i, str, path);
		}
		if (!path)
			cd_erro(argv, env);
		if (!path)
			return (NULL);
	}
	else
		path = str;
	return (path);
}

void	cd_ero(char **argv, t_data *env, char *str)
{
	free(str);
	fre(argv);
	env->status = 1;
	if (env->is_pipe)
		write_in_stdin("", true, env);
	printf("mishell: cd: HOME not set\n");
}

char	**ft_cd_temp(char *st, char **temp, int j)
{
	temp[j] = recover_word(st, 1 + j, false);
	if (no_quote(temp[j]) == 5)
		temp[j] = changeles(temp[j], '\'');
	else if (no_quote(temp[j]) == 0)
		temp[j] = changeles(temp[j], '"');
	if (temp[j])
	{
		j++;
		temp[j] = recover_word(st, 1 + j, false);
	}
	free(st);
	return (temp);
}
