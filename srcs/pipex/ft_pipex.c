/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:22:41 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/21 11:13:13 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	**cmd_with_option(char *str, char *path_ok, t_data *lst_data)
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
	while (buff)
	{
		tab_return = ft_realloc_tab(tab_return, 2);
		tab_return[j++] = ft_strdup(buff);
		free(buff);
		buff = recover_word(str, i++, false);
	}
	if (lst_data->here_doc)
	{
		tab_return = ft_realloc_tab(tab_return, 2);
		tab_return[j - 1] = ft_strdup("/proc/self/fd/0");
	}
	tab_return[j] = NULL;
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

static	char	*path_for_ex(char *cmd)
{
	char	*str_return;
	char	*cmd_tmp;
	char	tab[2];

	tab[0] = '/';
	tab[1] = '\0';
	cmd_tmp = recover_word(cmd, 1, false);
	if (access(cmd_tmp, X_OK | R_OK) == 0)
		return (ft_strdup(cmd_tmp));
	str_return = return_str_pwd();
	str_return = ft_strjoin(str_return, tab);
	str_return = ft_strjoin(str_return, cmd);
	return (str_return);
}

bool	ft_pipex(char *cmd, t_data *lst_data)
{
	char	*path_ok;
	char	**tab_with_opt;

	add_in_tab_path(lst_data);
	path_ok = checked_access(lst_data->lst_pipex.tab_path, cmd);
	if (!path_ok && ft_strchr(cmd, '/'))
		path_ok = path_for_ex(cmd);
	else if (!path_ok)
		return (NULL);
	tab_with_opt = cmd_with_option(cmd, path_ok, lst_data);
	lst_data->here_doc = false;
	if (execve(path_ok, tab_with_opt, lst_data->env) == -1)
	{
		printf("execve\n");
		return (false);
	}
	return (true);
}
