/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export13.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:37:31 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 10:37:33 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*verif(char *a)
{
	size_t	i;
	char	*b;

	b = NULL;
	if (a[0])
	{
		i = 0;
		b = ft_calloc(sizeof(char), ft_strlen(a) + 1);
		while (i != ft_strlen(a))
		{
			if ((a[i] <= 90 && a[i] >= 65)
				|| (a[i] <= 122 && a[i] >= 97))
				i = suiteverif(i, a);
			else if (a[i])
			{
				b = veriff(a, b, i);
				return (b);
			}
			if (i != ft_strlen(a))
				i++;
		}
	}
	b = anothersuite(b);
	return (b);
}

char	*deletes_for_no_mess(char *str, char *env, int j, t_data *en)
{
	int		a;
	size_t	i;
	char	*res;

	res = ft_calloc(sizeof(char), ft_strlen(env) + 2);
	j = 0;
	a = 0;
	while (env[j])
	{
		i = 0;
		if (j != 0 && (env[j - 1] == ' '
				|| env[j - 1] == '"' || env[j - 1] == '\''))
			while ((str[i] == env[j + i] && str[i] && env[j + i]))
				i++;
		else if (j == 0)
			while ((str[i] == env[j + i] && str[i] && env[j + i]))
				i++;
		if (i == ft_strlen(str) && (env[i + j] == ' ' || env[i + j] == '\0'
				|| env[i + j] == '"' || env[j + i] == '\''))
			j = j + i;
		res[a++] = env[j++];
	}
	free(env);
	free(en->t);
	return (res);
}

int	double_single(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((s1[i] != '\0' || s2[j] != '\0') && i < n)
	{
		if (s1[i] == '"')
			while (s1[i] == '"')
				i++;
		if (s2[j] == '\'')
			while (s2[j] == '\'')
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

int	single_double(char *s1, char *s2, int n)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while ((s1[i] != '\0' || s2[j] != '\0') && i < n)
	{
		if (s1[i] == '\'')
			while (s1[i] == '\'')
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

int	single_single(char *s1, char *s2, int n)
{
	int	i;
	int	j;

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
