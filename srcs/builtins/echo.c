/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/29 16:40:26 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	gest symbole " end ' end $
*/
static char	**gest_symbole(char *str, int start, int finish, bool opt)
{
	
	printf("pot = %d\n", start);
	printf("pot = %d\n", finish);
	printf("\ndecaler <%s>\n", str + start);
	printf("\ndecaler fini <%s>\n", str + finish);
	if (!opt)
		printf("\n");
	return (NULL);
}

/*
	pos_strat = index start string 
	return index finish string
*/
static int	word_has_print_return_pos_finish(char *str, int *pos_start)
{
	char	*opt;
	int		i;

	i = *pos_start;
	opt = recover_word(str, i);
	while (ft_strncmp(opt, "-n", 3) == 0)
	{
		free(opt);
		i++;
		opt = recover_word(str, i);
	}
	free(opt);
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
			|| str[i] == 13) && str[i])
		i++;
	*pos_start = i;
	i = 0;
	while (str[i])
		i++;
	i--;
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
			|| str[i] == 13) && str[i])
		i--;
	return (++i);
}

static char	**parssing_echo(char *str)
{
	char	*opt;
	int		i;
	int		j;
	bool	if_option;

	if_option = false;
	opt = recover_word(str, 2);
	if (ft_strncmp(opt, "-n", 2) == 0)
		if_option = true;
	i = 2;
	j = word_has_print_return_pos_finish(str, &i);
	i = recover_word_plus_return_position(str, --i);
	i++;
	free(opt);
	return (gest_symbole(str, i, j, if_option));
}

void	ft_echo(char *str)
{
	// char	**print_str;

	parssing_echo(str);
	// print_str = parssing_echo(str);
	printf("%s", str);
/* 	free(print_str); */
}
