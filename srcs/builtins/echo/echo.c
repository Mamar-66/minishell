/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/06 00:50:08 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	gest symbole " end ' end $
*/

static void	gest_symbole(char *str, int start)
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
		if ((buff[0] == '\''))
			buff_str = single_quote(buff);
		else if ((buff[0] == '"'))
			buff_str = double_quote(buff);
		else
			buff_str = simple_str(buff);
		str_return = ft_strjoin(str_return, buff_str);
		str_return = ft_strjoin(str_return, " ");
		//free(buff_str);
		//free(buff);
		buff = recover_word(str + start, ++i, false);
	}
	printf("%s", str_return);
	//free(buff);
}

/*
	verif is -n if true
	i = start str
	j = end str
*/

void	ft_echo(char *str)
{
	char	*opt;
	int		i;

	opt = recover_word(str, 2, false);
	i = 2;
	word_has_print_return_pos_finish(str, &i);
	i = recover_word_plus_return_position(str, --i);
	gest_symbole(str, i);
	if (ft_strncmp(opt, "-n", 3) != 0)
		printf("\n");
}
