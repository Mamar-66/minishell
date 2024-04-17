/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/17 20:34:38 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	gest symbole " end ' end $
*/
static void	gest_symbole(char *str, int start, t_data *lst_data)
{
	char	*buff_str;
	char	*str_return;
	char	*buff;

	str_return = ft_strdup("");
	buff = recover_word(str + start, 1, false);
	while (buff)
	{
		if (ft_strchr(buff, '\''))
			buff_str = quote(str + start, '\'', &start, false);
		else if (ft_strchr(buff, '"'))
			buff_str = quote(str + start, '"', &start, true);
		else
			buff_str = simple_str(str + start, lst_data, &start);
		str_return = ft_strjoin(str_return, buff_str);
		if (str[start] != '\'' && str[start] != '"')
			str_return = ft_strjoin(str_return, " ");
		while ((str[start] == 32 || str[start] == 9 || str[start] == 10
			|| str[start] == 13) && str[start])
			start++;
		// free(buff_str);
		// free(buff);
		buff = recover_word(str + start, 1, false);
	}
	printf(">%s<", str_return);
	free(buff);
}

void	ft_echo(char *str, t_data *lst_data)
{
	char	*opt;
	int		i;

	i = 2;
	opt = recover_word(str, 2, false);
	if (!opt)
	{
		printf("\n");
		return;
	}
	if (word_has_print_return_pos_finish(str, &i) != -1)
	{
		i = recover_word_plus_return_position(str, --i);
		gest_symbole(str, i, lst_data);
	}
	if (ft_strncmp(opt, "-n", 3) != 0)
		printf("\n");
}
