/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:09:22 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/15 14:09:24 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*anothersuite(char *b)
{
	if (b)
		free(b);
	b = ft_calloc(sizeof(char), 2);
	b[0] = 'a';
	return (b);
}

void	ft_error_and_status(t_data *en, char *str, int *z)
{
	(*z)++;
	en->status = 1;
	printf("minishell: export: `%s\': not a valid identifier\n", str);
}

void	ft_unsetbisbis(char *str, t_data *env, char *t)
{
	int		i;
	int		j;
	char	*test;

	j = 0;
	if (str)
	{
		i = 0;
		while (env->tenv[i])
		{
			if (ft_stcmp(str, env->tenv[i], ft_strlen(str)) == 0)
			{
				env->status = 1;
				printf("minishell: export: `%s\': not a valid identifier\n",
					env->tenv[i]);
				deletebis(i, env);
			}
			i++;
		}
		test = ft_calloc(sizeof(char), ft_strlen(env->t) + 4);
		ft_strlcpy(test, env->t, INT_MAX);
		if (!test)
			test = NULL;
		env->t = deletesbis(t, test, j, env);
	}
}

int	ft_scmp_bis(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while ((s1[i] != '\0' || s2[j] != '\0') && i < n)
	{
		if (s1[i] == '"')
			while (s1[i] == '"')
				i++;
		if (s2[j] == '"')
			while (s2[j] == '"')
				j++;
		if (s1[i] != s2[j])
			return ((unsigned char)s1[i] - (unsigned char)s2[j]);
		i++;
		j++;
	}
	if (s2[j] == '=' || s2[j] == '\0')
		return (0);
	return (1);
}

int	ft_scmp(char *s1, char *s2, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (no_quote(s1) == 5 && no_quote(s2) == 5)
	{
		j = single_single(s1, s2, n);
		return (j);
	}
	else if (no_quote(s1) == 5 && no_quote(s2) != 5)
	{
		j = single_double(s1, s2, n);
		return (j);
	}
	else if (no_quote(s1) == 0 && no_quote(s2) == 5)
	{
		j = double_single(s1, s2, n);
		return (j);
	}
	if (s2[j] == '=' || s2[j] == '\0')
		return (0);
	return (1);
}
