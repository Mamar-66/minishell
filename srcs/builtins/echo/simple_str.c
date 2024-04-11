/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:21:39 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/08 14:33:59 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char *val_var(char *str, int *ptr, t_data *lst_data)
{
	char	*str_return;
	char	*var;
	int		i_j[2];

	i_j[0] = -1;
	i_j[1] = 0;
	if (str[0] == '?')
	{
		str_return = ft_strdup(ft_itoa(lst_data->status));
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
	str_return = getenv(var);
	*ptr += i_j[1];
	free(var);
	return (str_return);
}

static char	*gest_global_var(char *str, t_data *lst_data)
{
	char	*str_return;
	char 	c[1];
	char 	*var;
	int 	i;

	i = -1;
	c[1] = '\0';
	str_return = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != '\n')
		{
			var = val_var(str + ++i, &i, lst_data);
			if (var)
				str_return = ft_strjoin(str_return, var);
			else
				str_return = ft_strjoin(str_return, " ");
		}
		else
		{
			c[0] = str[i];
			str_return = ft_strjoin(str_return, c);
		}
	}
	return (str_return);
}

char	*simple_str(char *str, t_data *lst_data, int *val_ptr)
{
	char	*str_return;
	int		i;

	i = 0;
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
		|| str[i] == 13) && str[i])
		i++;
	str_return = gest_global_var(str + i, lst_data);
	*val_ptr += ft_strlen(str_return);
	return (str_return);
}
