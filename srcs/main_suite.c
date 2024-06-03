/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:06:37 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/31 08:56:10 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	av_ex(char *cmd)
{
	if (cmd[0] == '|')
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	return (true);
}

void	affiche_in_terminal(t_data *lst_data,
	char *readline_recover, char **tab_arm_pipe)
{
	char	buff[25555];

	ft_bzero(buff, 25555);
	if (lst_data->mod_lectur_for_read_final && readline_recover[0]
		&& tab_arm_pipe[0])
	{
		read(STDIN_FILENO, buff, 25555);
		printf("%s", buff);
	}
}
