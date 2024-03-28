/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/28 15:44:28 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	parssing_echo(char *str)
{
	int		i;
	int		j;

	i = 2;
	j = word_has_print_return_pos_finish(str, &i);
	i = recover_word_plus_return_position(str, --i);
	printf("pot = %d\n", i);
	printf("pot = %d\n", j);
	printf("\ndecaler <%s>\n", str + i);
	printf("\ndecaler fini <%s>\n", str + j);
}

void	ft_echo(char *str)
{
	char	*opt;
	// char	*print_str;
	bool	if_option;

	if_option = false;
	opt = recover_word(str, 2);
	if (ft_strncmp(opt, "-n", 2) == 0)
		if_option = true;
	parssing_echo(str);
	if (!if_option)
		printf("%s\n", str);
	else
		printf("%s", str);
	free(opt);
	// free(print_str);
}
