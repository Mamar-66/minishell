/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/16 11:52:07 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo(char *str)
{
	char	*opt;
	int		i;
	int		j;

	i = 2;
	opt = recover_word(str, 2, false);
	if (!opt)
	{
		free(opt);
		printf("\n");
		return ;
	}
	if (word_has_print_return_pos_finish(str, &i) != -1)
	{
		i = recover_word_plus_return_position(str, --i);
		j = i;
		while (str[j])
		{
			write(STDOUT_FILENO, &str[j], 1);
			j++;
		}
	}
	if (!verif_n(opt))
		printf("\n");
	free(opt);
}
