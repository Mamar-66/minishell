/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:21:39 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/05 17:46:35 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char *val_var(char *str, int *ptr)
{
	char	*str_return;
	char	*var;
	int		i;
	int 	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '_')
			j++;
		else
			break ;
		i++;
	}
	var = malloc(sizeof(char) * j + 1);
	if (!var)
		return (NULL);
	ft_strlcpy(var, str + (i - j), j + 1);
	str_return = getenv(var);
	*ptr += j;
	free(var);
	return (str_return);
}

static char	*gest_global_var(char *str)
{
	char	*str_return;
	char	*var;
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			var = val_var(str + i + 1, &i);
			if (var)
				str_return = ft_strjoin(str_return, var);
		}
		else
			str_return = ft_strjoin_caract(str_return, str[i]);
	}
	return (str_return);
}

char	*simple_str(char *str)
{
	char	*str_return;

	str_return = gest_global_var(str);
	return (str_return);
}
