/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:43 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/06 12:31:25 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_stcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i] == '=' || s2[i] == '\0')
		return (0);
	else
		return (1);
}

void	delete(int i, t_data *env)
{
	free(env->tenv[i]);
	while (env->tenv[i])
	{
		env->tenv[i] = env->tenv[i + 1];
		i++;
	}
}

int	suitedelete(char *env, int i, int j)
{
	if (env[i + j] == '=')
		while (env[i + j] != ' ' && env[i + j] != '\0')
			j++;
	j = j + i;
	return (j);
}

char	*deletes(char *str, char *env, int a)
{
	int		j;
	size_t	i;
	char	*res;

	res = ft_calloc(sizeof(char), ft_strlen(env) + 1);
	j = 0;
	while (env[j])
	{
		i = 0;
		if (j != 0 && env[j - 1] == ' ')
			while (str[i] == env[j + i] && str[i] && env[j + i]
				&& str[i] != '=' && env[j + i] != '=')
				i++;
		else if (j == 0)
			while (str[i] == env[j + i] && str[i]
				&& env[j + i] && str[i] != '=' && env[j + i] != '=')
				i++;
		if (i == ft_strlen(str)
			&& (env[i + j] == ' ' || env[i + j] == '\0' || env[i + j] == '='))
			j = suitedelete(env, i, j);
		res[a++] = env[j++];
	}
	free(env);
	return (res);
}

void	ft_unset(char *str, t_data *env, char *st)
{
	int		i;
	int		j;
	int		a;
	char	*t;
	char	**argv;

	(void)st;
	t = NULL;
	j = -1;
	argv = ft_calloc(sizeof(char *), 30);
	argv[j + 1] = recover_word(str, j + 2, false);
	while (argv[++j])
		argv[j + 1] = recover_word(str, j + 2, false);
	j = -1;
	while (argv[++j])
		ft_unsetbi(argv[j], env);
	a = 0;
	i = 0;
	changeenv(env->tenv, env);
	if (env->is_pipe)
		write_in_stdin("", true, env);
	fre(argv);
}
