/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:33:35 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/13 13:33:36 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	good(char **trier)
{
	int	i;
	int	j;

	i = 0;
	while (trier[i + 1])
	{
		j = 0;
		if (trier[i][j] > trier[i + 1][j])
			return (1);
		while (trier[i + 1] && trier[i][j] && trier[i][j + 1]
		&& trier[i][j] == trier[i + 1][j])
		{
			j++;
			if (trier[i][j] > trier[i + 1][j])
				return (1);
		}
		i++;
	}
	return (0);
}

char	*ajoute2(char *argv, int j, char s, char t)
{
	while (argv[j])
	{
		if (j > 0 && argv[j] == '=')
		{
			j++;
			t = argv[j];
			argv[j] = '\"';
			j++;
			s = argv[j];
			argv[j] = t;
			j++;
			while (argv[j - 1])
			{
				t = argv[j];
				argv[j] = s;
				j++;
				s = argv[j];
				argv[j] = t;
				j++;
			}
		}
		j++;
	}
	return (argv);
}

char	**ajoute(char **argv)
{
	int		i;
	int		j;
	char	t;
	char	s;

	i = 0;
	s = 'a';
	t = 'a';
	while (argv[i])
	{
		j = 0;
		argv[i] = ajoute2(argv[i], j, s, t);
		i++;
	}
	return (argv);
}

char	**trie2(char **trier, char **temp, int i)
{
	int	j;

	while (trier[i + 1])
	{
		j = 0;
		if (trier[i][0] > trier[i + 1][0])
		{
			temp[0] = trier[i];
			trier[i] = trier[i + 1];
			trier[i + 1] = temp[0];
		}
		while (trier[i + 1] && trier[i][j] && trier[i + 1][j]
		&& trier[i][j] == trier[i + 1][j])
		{
			j++;
			if (trier[i][j] > trier[i + 1][j])
			{
				temp[0] = trier[i];
				trier[i] = trier[i + 1];
				trier[i + 1] = temp[0];
			}
		}
		i++;
	}
	return (trier);
}
