/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_readline_recover.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:32 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/02 12:34:27 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 	return 1 if built otherwise return 0 is cmd
// !!!!!!!
// 		attention Simon le belge le printf 
// 		de command not found se n'est pas sa place finale
// 		par ce que y a pas les commande comme ls et tout \addindex
//		en etait verifier avec pipex ;)
// !!!!!!!!

static bool	built_or_cmd(char *str)
{
	char	*cmd;

	cmd = recover_word(str, 1, false);
	if (ft_strncmp_ign_del(cmd, "echo", 5) == 0)
		ft_echo(str);
	else if (ft_strncmp_ign_del(cmd, "pwd", 4) == 0)
		ft_pwd();
	else
	{
		printf(": command not found\n");
		free(cmd);
		return (0);
	}
	free(cmd);
	return (1);
}

bool	gest_readline_recover(char *str, t_data *lst_data)
{
	if (str)
	{
		built_or_cmd(str);
		dup2(lst_data->fd_saved_std_out, STDOUT_FILENO);
	}
	return (false);
}
/* 
	else if (ft_strncmp(text, "cd", 2) == 0)
	else if (ft_strncmp(text, "export", 6) == 0)
	else if (ft_strncmp(text, "unset", 5) == 0)
	else if (ft_strncmp(text, "env", 3) == 0)
	else if (ft_strncmp(text, "exit", 4) == 0)
 */