/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:09:19 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/24 11:55:42 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	*if_space_end_wedspace(char *str_return, char *str,
	char *buff, int *start)
{
	(void)buff;
	int		i;
	char	*ft_str_return;

	i = *start;
		while ((str[i] == 32 || str[i] == 9 || str[i] == 10
				|| str[i] == 13) && str[i])
				i++;
		if (i != *start)
			ft_str_return = ft_strjoin(str_return, " ");
		else
		{
			ft_str_return = ft_strdup(str_return);
			free(str_return);
		}
	*start = i;
	return (ft_str_return);
}

static	char	*gest_symbole_plus(char *str, char *buff, t_data *lst_data)
{
	char	*buff_return;

	if (ft_strchr(buff, '\'') && ft_strchr(buff, '"'))
	{
		if (ft_strchr(buff, '\'') < ft_strchr(buff, '"'))
			buff_return = quote(str, lst_data, '\'', false);
		else
			buff_return = quote(str, lst_data, '"', false);
	}
	else if (ft_strchr(buff, '\''))
		buff_return = quote(str, lst_data, '\'', false);
	else if (ft_strchr(buff, '"'))
		buff_return = quote(str, lst_data, '"', true);
	else if (buff)
		buff_return = simple_str(str, lst_data);
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
	buff_str = NULL;
	buff = recover_word(str + start, 1, false);
	while (buff)
	{
		buff_str = gest_symbole_plus(str + start, buff, lst_data);
		start += ft_strlen(buff);
		str_return = ft_strjoin(str_return, buff_str);
		str_return = if_space_end_wedspace(str_return, str, buff, &start);
		free(buff_str);
		free(buff);
		buff = recover_word(str + start, 1, false);
		printf("buff = %s\n", buff);
	}
	free(buff);
	return (str_return);
}

char	*parsing(char *str, t_data *lst_data)
{
	char	*str_return;

	str_return = gest_symbole(str, 0, lst_data);
	free(str);
	return (str_return);
}
