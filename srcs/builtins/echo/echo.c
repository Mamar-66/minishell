/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/24 11:12:08 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo(char *str, t_data *lst_data)
{
	(void)lst_data;
	char	*opt;
	int		i;

	i = 2;
	opt = recover_word(str, 2, false);
	if (!opt)
	{
		printf("\n");
		return ;
	}
	if (word_has_print_return_pos_finish(str, &i) != -1)
	{
		i = recover_word_plus_return_position(str, --i);
		printf("<%s>", str + i);
	}
	if (ft_strncmp(opt, "-n", 3) != 0)
		printf("\n");
	free(opt);
}
