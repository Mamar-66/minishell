/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:09:19 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/11 15:17:56 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	*if_space_end_wedspace(char *str_return, char *str,
	char *buff, int *start)
{
	int		i;
	char	*ft_str_return;

	i = *start;
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
			|| str[i] == 13) && str[i])
		i++;
	if (i != *start && buff[0] != '>')
		ft_str_return = ft_strjoin(str_return, " ");
	else
	{
		ft_str_return = ft_strdup(str_return);
		free(str_return);
	}
	*start = i;
	return (ft_str_return);
}

static char	*gest_symbole_plus(char *buff, char *str
	, int *start, t_data *lst_data)
{
	char	*buff_return;

	buff_return = NULL;
	if (buff[0] == '\'')
		buff_return = quote(buff, lst_data);
	else if (buff[0] == '"')
		buff_return = quote(buff, lst_data);
	else if (buff)
		buff_return = simple_str(buff, str, start, lst_data);
	lst_data->pour_toi_simon++;
	return (buff_return);
}

char	*pour_toi_omar(char *str)
{
	int		i;
	int		j;
	int		a;
	char	*new_str;

	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 10);
	i = 0;
	j = 0;
	a = 0;
	while (str[j])
	{
		new_str[i] = str[j];
		if (str[j + 1] == '<' && str[j] != '<' && a == 0)
		{
			a++;
			new_str[++i] = ' ';
		}
		j++;
		i++;
	}
	free(str);
	return (new_str);
}
/*
	gest symbole " end ' end $
*/

static	char	*gest_symbole(char *str, int start, t_data *lst_data)
{
	char	*buff_str;
	char	*str_return;
	char	*buff;

	str = pour_toi_omar(str);
	str_return = ft_strdup("");
	buff = recover_word(str + start, 1, false);
	while (buff)
	{
		buff_str = gest_symbole_plus(buff, str, &start, lst_data);
		if (!buff_str)
		{
			free(buff_str);
			free(buff);
			return (free(str), free(str_return), NULL);
		}
		start += ft_strlen(buff);
		str_return = ft_strjoin(str_return, buff_str);
		str_return = if_space_end_wedspace(str_return, str, buff, &start);
		free(buff_str);
		free(buff);
		buff = recover_word(str + start, 1, false);
	}
	return (free(str), free(buff), str_return);
}

char	*parsing(char *str, t_data *lst_data)
{
	char	*str_return;
	int		i;

	i = 0;
	ft_change_numsignal(lst_data);
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
			|| str[i] == 13) && str[i])
		i++;
	str_return = gest_symbole(ft_strdup(str + i), 0, lst_data);
	if (!str_return)
	{
		return (free(str), NULL);
	}
	if (str_return && ft_strncmp(str_return, "", 1) == 0)
	{
		free(str_return);
		str_return = NULL;
	}
	if (str_return && str_return[ft_strlen(str_return) - 1] == ' ')
		str_return[ft_strlen(str_return) - 1] = '\0';
	if (str_return && lst_data->here_doc && lst_data->here_doc_parssing)
		str_return = ft_strjoin(str_return, "\n");
	free(str);
	return (str_return);
}
