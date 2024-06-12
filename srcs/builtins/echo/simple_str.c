/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:21:39 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/11 14:37:59 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static	char	*val_varr(char *str, int *ptr, t_data *lst_data)
// {
// 	char	*str_return;
// 	char	*var;
// 	int		i_j[2];

// 	i_j[0] = -1;
// 	i_j[1] = 0;
// 	if (str[0] == '?')
// 	{
// 		*ptr += 1;
// 		return (ft_itoa(lst_data->status));
// 	}
// 	while (str[++i_j[0]])
// 	{
// 		if (ft_isalpha(str[i_j[0]]) || str[i_j[0]] == '_')
// 			i_j[1]++;
// 		else
// 			break ;
// 	}
// 	var = malloc(sizeof(char) * i_j[1] + 1);
// 	if (!var)
// 		return (NULL);
// 	ft_strlcpy(var, str + (i_j[0] - i_j[1]), i_j[1] + 1);
// 	str_return = ft_getenv(lst_data->env, var);
// 	*ptr += i_j[1];
// 	return (free(var), str_return);
// }

static char	*gest_global_var(char *str, t_data *lst_data)
{
	char	*str_return;
	char	c[2];
	char	*var;
	int		i;

	i = -1;
	c[0] = 127;
	c[1] = '\0';
	str_return = ft_strdup("");
	while (str[++i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
	{
		c[0] = str[i];
		if (str[i] == '$' && str[i + 1] != '\n'
			&& str[i + 1] != ' ' && str[i + 1])
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

char	*simple_str(char *buff, char *str, int *start, t_data *lst_data)
{
	char	*str_return;
	char	*buff_intern;

	buff_intern = redirect(buff, str, start, lst_data);
	if (!buff_intern)
	{
		free(buff_intern);
		return (NULL);
	}
	str_return = gest_global_var(buff_intern, lst_data);
	free(buff_intern);
	return (str_return);
}
