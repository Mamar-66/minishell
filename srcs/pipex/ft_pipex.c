/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:22:41 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/13 17:12:10 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **cmd_with_option(char *str, char *path_ok)
{
	char	**tab_return;
	char	*buff;
	int		i;
	int		j;

	i = 2;
	j = 1;
	tab_return = ft_calloc(sizeof(char *), 2);
	tab_return[0] = ft_strdup(path_ok);
	buff = recover_word(str, i++, false);
	while(buff && buff[0] == '-')
	{
		tab_return = ft_realloc_tab(tab_return, 2);
		tab_return[j++] = ft_strdup(buff);
		free(buff);
		buff = recover_word(str, i++, false);
	}
	return (tab_return);
}

static char	*checked_access(char **tab_path, char *cmd)
{
	char	*path_cmd;
	char	*cmd_tmp;
	int		j;

	j = -1;
	if (!cmd)
		return (NULL);
	cmd_tmp = recover_word(cmd, 1, false); 
	while (tab_path[++j])
	{
		path_cmd = ft_strdup(tab_path[j]);
		path_cmd = ft_realloc(path_cmd, ft_strlen(cmd_tmp) + 1);
		ft_strlcat(path_cmd, "/",
			ft_strlen(tab_path[j]) + ft_strlen(cmd_tmp) + 1);
		ft_strlcat(path_cmd, cmd_tmp,
			ft_strlen(tab_path[j]) + ft_strlen(cmd_tmp) * 3);
		if (access(path_cmd, X_OK | R_OK) == 0)
			break ;
		free(path_cmd);
	}
	free(cmd_tmp);
	if (tab_path[j])
		return (path_cmd);
	else
		return (NULL);
}

static void	add_in_tab_path(t_data *lst_data)
{
	int	j;

	j = 0;
	while (lst_data->env[j])
	{
		if (ft_strncmp(lst_data->env[j], "PATH=", 4) == 0)
			break ;
		j++;
	}
	lst_data->lst_pipex.tab_path = ft_split(lst_data->env[j] + 5, ':');
}

bool	ft_pipex(char *cmd, t_data *lst_data)
{
	char	*path_ok;
	char	**tab_with_opt;

	add_in_tab_path(lst_data);
	path_ok = checked_access(lst_data->lst_pipex.tab_path, cmd);
	tab_with_opt = cmd_with_option(cmd, path_ok);
	if (execve(path_ok, tab_with_opt, NULL) == -1)
	{
		perror("error execve ");
		return (false);
	}
	return (true);
}
