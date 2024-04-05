/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/05 15:05:00 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


/*
	gest symbole " end ' end $
*/

static char	*gest_symbole(char *str, int start, int finish)
{
	(void)finish;
	char	*str_parssing;
	char	*buff;
	int		i;

	i = 1;
	buff = recover_word(str + start, i, false);
	while (buff)
	{
		if ((buff[0] == '\''))
			buff = single_quote(buff);
		else if ((buff[0] == '"'))
			double_quote(buff);
		else
			buff = recover_word(str + start, i, false);
		printf("\n>%s<\n", buff);
		return (NULL);
	}
	free(buff);
	str_parssing = NULL;
	return (str_parssing);
}

/*
	verif is -n if true
	i = start str
	j = end str
*/
static char	*parssing_echo(char *str)
{
	char	*str_return;
	// char	*opt;
	int		i;
	int		j;

	// opt = recover_word(str, 2);
	i = 2;
	j = word_has_print_return_pos_finish(str, &i);
	i = recover_word_plus_return_position(str, --i);
	// printf("test >%s<\n", str + i);
	// printf("test fin >%s<\n", str + j);
	str_return = gest_symbole(str, i, j);
	// if (ft_strncmp(opt, "-n", 3) != 0)
	// 	str_return = ft_strjoin(str_return, "\n");
	// free(opt);
	return (str_return);
}

void	ft_echo(char *str)
{
	char	*print_str;

	// parssing_echo(str);
	// print_str = recover_word(str, 2);
	print_str = parssing_echo(str);
	printf("%s", print_str);
	// printf("%s", str);
	free(print_str);
}
