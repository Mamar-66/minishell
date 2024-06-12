/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:33:40 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/04 17:30:13 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	findn(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '=')
				return (i);
			i++;
		}
	}
	return (0);
}

int	nodif(char *str, char *s)
{
	int	i;

	i = 0;
	if (findn(str) == findn(s) && findn(str) != 0)
	{
		while (str[i] && i != findn(str))
		{
			if (str[i] != s[i])
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	print3(char **temp, int i)
{
	int	j;
	int	a;

	a = 0;
	if (ft_strncmp(temp[i], "_=\"/home", 7) == 0)
		return (i);
	if (temp[i][0] != 127)
		printf("declare -x %s\"\n", temp[i]);
	j = i;
	if (temp[i + 1])
	{
		while (temp[i + 1] && a != 1 && nodif(temp[j], temp[i + 1]) == 1)
		{
			if (temp[i + 1])
				i++;
			else
				a = 1;
		}
	}
	return (i);
}

int	print2(char **temp, int i)
{
	int	j;
	int	a;

	a = 0;
	if (temp[i][0] != 127)
		printf("declare -x %s\n", temp[i]);
	j = i;
	if (temp[i + 1])
	{
		while (temp[i + 1] && a != 1
			&& ft_strncmp(temp[j], temp[i + 1], 200) == 0)
		{
			if (temp[i + 1])
				i++;
			else
				a = 1;
		}
	}
	return (i);
}

void	print(char **temp, t_data *en)
{
	int		i;
	char	*rev;

	i = 0;
	if (!en->is_pipe)
	{
		while (temp[i])
		{
			while (temp[i][0] == '5')
				i++;
			if (findn(temp[i]) != 0)
				i = print3(temp, i);
			else
				i = print2(temp, i);
			i++;
		}
	}
	else
	{
		rev = inverse_split_export(temp);
		write_in_stdin(rev, true, en);
		free(rev);
	}
}
