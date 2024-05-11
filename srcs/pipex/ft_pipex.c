/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:22:41 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/11 13:49:58 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **cmd_with_option(char *str)
{
	char	**tab_return;
	char	*buff;
	int		i;

	i = 1;
	tab_return = malloc(sizeof(char *) *  1);
	tab_return[0] = recover_word(str, i, false);
	buff = recover_word(str, i++, false);
	while(buff[0] == '-')
	{
		tab_return = ft_realloc_tab(tab_return, 1);
		tab_return[i] = ft_strdup(buff);
		buff = recover_word(str, i++, false);
	}
	tab_return = ft_realloc_tab(tab_return, 1);
	tab_return[i] = '\0';
	return (tab_return);
}

static char	*checked_access(char **tab_path, char *cmd)
{
	char	*path_cmd;
	int		j;

	j = 0;
	if (!cmd)
		return (NULL);
	while (tab_path[j])
	{
		path_cmd = ft_strdup(tab_path[j]);
		path_cmd = ft_realloc(path_cmd, ft_strlen(cmd) + 1);
		ft_strlcat(path_cmd, "/",
			ft_strlen(tab_path[j]) + ft_strlen(cmd) + 1);
		ft_strlcat(path_cmd, cmd,
			ft_strlen(tab_path[j]) + ft_strlen(cmd) * 3);
		if (access(path_cmd, X_OK | R_OK) == 0)
			break ;
		free(path_cmd);
		j++;
	}
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
	tab_with_opt = cmd_with_option(cmd);
	printf("pipex = %s\n", cmd);
	if (execve(path_ok, tab_with_opt, NULL) == -1)
	{
		perror("error execve ");
		return (false);
	}
	return (true);
}
