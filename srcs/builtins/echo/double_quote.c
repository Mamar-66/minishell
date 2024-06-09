/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:11:45 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/08 15:27:01 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*val_var(char *str, int *ptr, t_data *lst_data)
{
	char	*str_return;
	char	*var;
	int		i_j[2];

	i_j[0] = -1;
	i_j[1] = 0;
	if (str[0] == '?')
	{
		*ptr += 1;
		str_return = ft_itoa(lst_data->status);
		return (str_return);
	}
	while (str[++i_j[0]])
		if (ft_isalpha(str[i_j[0]]) || str[i_j[0]] == '_')
			i_j[1]++;
	else
		break ;
	var = malloc(sizeof(char) * i_j[1] + 1);
	if (!var)
		return (NULL);
	ft_strlcpy(var, str + (i_j[0] - i_j[1]), i_j[1] + 1);
	str_return = ft_getenv(lst_data->env, var);
	*ptr += i_j[1];
	free(var);
	return (str_return);
}

static char	*gest_global_var(char *str, t_data *lst_data)
{
	char	*str_return;
	char	c[2];
	char	*var;
	int		i;

	i = -1;
	c[1] = '\0';
	str_return = ft_strdup("");
	while (str[++i])
	{
		c[0] = str[i];
		if (str[i] == '$' && str[i + 1] != '\n'
			&& str[i + 1] != ' ' && str[i + 1] != '"'
			&& str[i + 1] > 32 && str[i + 1] < 127)
		{
			var = val_var(str + i + 1, &i, lst_data);
			if (var)
				str_return = ft_strjoin(str_return, var);
			if (var)
				free(var);
		}
		else
			str_return = ft_strjoin(str_return, c);
	}
	return (str_return);
}

char	*double_quote(char *str, t_data *lst_data)
{
	char	*str_return;

	str_return = gest_global_var(str, lst_data);
	free(str);
	return (str_return);
}
