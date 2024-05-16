/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_readline_recover.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:32 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/16 14:04:46 by omfelk           ###   ########.fr       */
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

static void	suiteexit(char *cmd, char *str, t_data *env, char **argv)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(str + 4);
	fre(argv);
	free(cmd);
	ft_exit(temp, env);
}

bool	built_or_cmd_for_father(char *str, t_data *lst_data,
			char **tab_arm_pipe)
{
	char	*cmd;

	lst_data->mod_lectur_for_read_final = false;
	cmd = recover_word(str, 1, false);
	if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(str, lst_data);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(str, lst_data);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(str, lst_data);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(str + 6, lst_data);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		suiteexit(cmd, str, lst_data, tab_arm_pipe);
	else
	{
		free(cmd);
		return (false);
	}
	free(cmd);
	return (true);
}

static bool	built_or_cmd(char *str, t_data *lst_data)
{
	char	*cmd;

	cmd = recover_word(str, 1, false);
	if (ft_strncmp_ign_del(cmd, "echo", 5) == 0)
		ft_echo(str);
	else if (ft_strncmp_ign_del(cmd, "pwd", 4) == 0)
		ft_pwd();
	else if (!ft_pipex(str, lst_data))
	{
		printf("%s: command not found\n", cmd);
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
		built_or_cmd(str, lst_data);
	}
	return (false);
}
