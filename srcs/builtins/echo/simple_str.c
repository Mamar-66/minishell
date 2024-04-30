/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:21:39 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/30 15:37:46 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	char	*val_var(char *str, int *ptr, t_data *lst_data)
{
	char	*str_return;
	char	*var;
	int		i_j[2];

	i_j[0] = -1;
	i_j[1] = 0;
	if (str[0] == '?')
	{
		*ptr += 1;
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
	char	c[1];
	char	*var;
	int		i;

	i = -1;
	c[1] = '\0';
	str_return = ft_strdup("");
	while (str[++i] && str[i] != ' ' && str[i] != '\'' && str[i] != '"')
	{
		if (str[i] == '$' && str[i + 1] != '\n'
			&& str[i + 1] != ' ' && str[i + 1])
		{
			var = val_var(str + i + 1, &i, lst_data);
			if (var)
				str_return = ft_strjoin(str_return, var);
		}
		else
		{
			c[0] = str[i];
			str_return = ft_strjoin(str_return, c);
		}
	}
	// free(str);
	return (str_return);
}

char	*simple_str(char *buff, char *str, int *start, t_data *lst_data)
{
	char	*str_return;

	str_return = redirect(buff, str, start, lst_data);
	if (!str_return)
	{
		printf("bash: syntax error file name not defined\n");
		return (NULL);
	}
	str_return = gest_global_var(str_return, lst_data);
	return (str_return);
}
