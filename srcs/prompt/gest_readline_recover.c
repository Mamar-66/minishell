/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_readline_recover.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:01:32 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/05 15:22:37 by omfelk           ###   ########.fr       */
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

static	void	write_error(char *cmd, t_data *lst_data)
{
	char	*text;
	int		fd;

	fd = open("/dev/tty", O_WRONLY);
	text = parsing(ft_strdup(cmd), lst_data);
	if (ft_strchr(text, '/'))
	{
		write(fd, text, ft_strlen(text));
		write(fd, " : Is a directory\n", ft_strlen(": Is a directory\n"));
	}
	else
	{
		write(fd, text, ft_strlen(text));
		write(fd, " \x1b[31m: command not found\x1b[0m\n",
			ft_strlen(" \x1b[31m: command not found\x1b[0m\n"));
	}
	close(fd);
	free(text);
}

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
			char **tab_arm_pipe, char *str_reel)
{
	char	*cmd;
	char	*cmd1;

	lst_data->status = 0;
	lst_data->mod_lectur_for_read_final = false;
	cmd = recover_word(str, 1, false);
	cmd1 = recover_word(str_reel, 1, false);
	if (ft_strncmp(cmd, "env", 4) == 0)
		ft_env(str, lst_data);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		ft_export(str, lst_data);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		ft_cd(str, lst_data);
	else if ((ft_strncmp(cmd, "echo", 5) == 0 && ft_strlen(cmd1) <= 6))
		ft_echo(str, lst_data);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		ft_unset(str + 5, lst_data);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		suiteexit(cmd, str, lst_data, tab_arm_pipe);
	else if (ft_strncmp_ign_del(cmd, "pwd", 4) == 0 && ft_strlen(cmd1) <= 5)
		ft_pwd(lst_data);
	else
		return (free(cmd), free(cmd1), false);
	return (free(cmd), free(cmd1), true);
}

static bool	built_or_cmd(char *str, t_data *lst_data, char *reel)
{
	char	*cmd;
	char	*cmd1;

	cmd = recover_word(str, 1, false);
	cmd1 = recover_word(reel, 1, false);
	if (!ft_pipex(str, lst_data))
	{
		lst_data->status = 127;
		write_error(cmd1, lst_data);
		return (free(cmd), free(cmd1), 0);
	}
	lst_data->status = 0;
	return (free(cmd), free(cmd1), 1);
}

bool	gest_readline_recover(char *str, t_data *lst_data, char *reel)
{
	if (str)
	{
		built_or_cmd(str, lst_data, reel);
	}
	return (false);
}
