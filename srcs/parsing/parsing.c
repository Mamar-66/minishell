/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:09:19 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/19 10:54:10 by omfelk           ###   ########.fr       */
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

static	char	*gest_symbole_plus(char *buff, char *str
	, int *start, t_data *lst_data)
{
	char	*buff_return;

	if (buff[0] == '\'')
		buff_return = quote(buff, lst_data);
	else if (buff[0] == '"')
		buff_return = quote(buff, lst_data);
	else if (buff)
		buff_return = simple_str(buff, str, start, lst_data);
	return (buff_return);
}

/*
	gest symbole " end ' end $
*/
static char	*gest_symbole(char *str, int start, t_data *lst_data)
{
	char	*buff_str;
	char	*str_return;
	char	*buff;

	str_return = ft_strdup("");
	buff = recover_word(str + start, 1, false);
	while (buff)
	{
		buff_str = gest_symbole_plus(buff, str, &start, lst_data);
		if (!buff_str)
		{
			free(buff_str);
			free(buff);
			free(str_return);
			return (NULL);
		}
		start += ft_strlen(buff);
		str_return = ft_strjoin(str_return, buff_str);
		str_return = if_space_end_wedspace(str_return, str, buff, &start);
		free(buff_str);
		free(buff);
		buff = recover_word(str + start, 1, false);
	}
	free(buff);
	return (str_return);
}

char	*parsing(char *str, t_data *lst_data)
{
	char	*str_return;
	int		i;

	i = 0;
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
			|| str[i] == 13) && str[i])
		i++;
	str_return = gest_symbole(str + i, 0, lst_data);
	if (!str_return)
		return (NULL);
	if (str_return && ft_strncmp(str_return, "", 1) == 0)
	{
		free(str_return);
		str_return = NULL;
	}
	if (str_return && str_return[ft_strlen(str_return) - 1] == ' ')
		str_return[ft_strlen(str_return) - 1] = '\0';
	if (str_return && lst_data->here_doc)
		str_return = ft_strjoin(str_return, "\n");
	free(str);
	return (str_return);
}
