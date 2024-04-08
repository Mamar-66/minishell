/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_readline_recover.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:32 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/08 13:52:51 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	return 1 if built otherwise return 0 is cmd
*/
static bool	built_or_cmd(char *str, t_data *lst_data)
{
	char	*text;

	text = recover_word(str, 1, false);
	if (ft_strncmp(text, "echo", 5) == 0)
		ft_echo(str, lst_data);
	else
	{
		perror(text);
		return (0);
	}
	return (1);
}

bool	gest_readline_recover(char *str, t_data *lst_data)
{
	if (*str)
	{
		built_or_cmd(str, lst_data);
		add_history(str);
	}
	return (false);
}
/* 
	else if (ft_strncmp(text, "cd", 2) == 0)
	else if (ft_strncmp(text, "pwd", 3) == 0)
	else if (ft_strncmp(text, "export", 6) == 0)
	else if (ft_strncmp(text, "unset", 5) == 0)
	else if (ft_strncmp(text, "env", 3) == 0)
	else if (ft_strncmp(text, "exit", 4) == 0)
 */