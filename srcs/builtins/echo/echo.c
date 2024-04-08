/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/08 17:40:52 by omfelk           ###   ########.fr       */
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
	int		i;

	i = 1;
	str_return = ft_strdup("");
	buff = recover_word(str + start, i, false);
	while (buff)
	{
		if (ft_strchr(buff, '\''))
			buff_str = single_quote(buff);
		else if (ft_strchr(buff, '"'))
			buff_str = double_quote(buff, lst_data);
		else
			buff_str = simple_str(buff, lst_data);
		str_return = ft_strjoin(str_return, buff_str);
		str_return = ft_strjoin(str_return, " ");
		//free(buff_str);
		//free(buff);
		buff = recover_word(str + start, ++i, false);
	}
	printf("%s", str_return);
	// free(buff);
}

/*
	verif is -n if true
	i = start str
	j = end str
*/

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
