/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export18.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:37:23 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/10 12:37:25 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	ft(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_line(int i, char *str, char *env, int j)
{
	if (i == (int)ft_strlen(str) && (env[i + j] == ' ' || env[i + j] == '\0'
			|| env[i + j] == '"' || env[j + i] == '\''
			|| env[i + j] == '='))
	{
		j = j + i;
		if (env[j] == '=')
			while (j < ((int)ft_strlen(env)) && env[j] != ' ')
				j++;
	}
	return (j);
}

int	only_space(char *str)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
