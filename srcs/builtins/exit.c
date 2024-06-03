/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:27 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/26 15:56:29 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long int	f_atoi(const char *nptr)
{
	long long int	retur;
	long long int	i;
	long long int	signe;

	retur = 0;
	i = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13)
		|| (nptr[i] == 32 && nptr[i] != '\0'))
		i++;
	if (nptr[i] == '-' || (nptr[i] == '+' && nptr[i] != '\0'))
	{
		if (nptr[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i] != '\0')
	{
		retur = retur * 10 + (nptr[i] - '0');
		i++;
	}
	retur = retur * signe;
	return (retur);
}

size_t	f(const char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i + j] != '\0')
	{
		if (s[i + j] == ' ')
			j++;
		else
			i++;
	}
	return (i);
}

void	ft_count(char *str)
{
	char	**temp;

	temp = NULL;
	temp = ft_split(str, ' ');
	printf("exit\n");
	if (temp && str[0])
	{
		if (temp[1] && str[0] != '\0')
		{
			printf("minishelle: exit: too many arguments\n");
			free(str);
			fre(temp);
			exit (1);
		}
	}
	fre(temp);
}

void	ft_numeric(char *str)
{
	printf("minishelle: exit: %s: numeric argument required\n", str);
	free(str);
	exit (2);
}

void	ft_exit(char *str, t_data *env)
{
	long long int	j;
	size_t			i;

	freeverithing(env);
	ft_count(str);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
		{
			if ((str[i] == '+' || str[i] == '-'))
				j++;
			i++;
			if (j >= 2 || ((str[i] < '0' || str[i] > '9') && (str[i] != ' ')))
				ft_numeric(str);
		}
	}
	j = f_atoi(str);
	if (f(str) > 20 || j > 9223372036854775807 || j < -9223372036854775807)
		ft_numeric(str);
	if (str[0] == '\0')
		j = 0;
	free(str);
	exit (j);
}
