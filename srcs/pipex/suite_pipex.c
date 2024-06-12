/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suite_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:57:21 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/12 16:41:07 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	if_grep(void)
{
	char	buffff[255555];
	int		fd;

	fd = open(" ", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	ft_bzero(buffff, 255555);
	read(STDIN_FILENO, buffff, 255555);
	if (buffff[0])
		write(fd, &buffff, ft_strlen(buffff) - 1);
	close(fd);
}

static	char	**push_stdin(char	**tab_return, int *start, t_data *lst_data)
{
	int		j;
	char	**tab_r;

	j = *start;
	tab_r = ft_realloc_tab(tab_return, 1, true);
	if (!ft_strncmp(tab_r[0], "/usr/bin/grep", INT_MAX))
	{
		tab_r = ft_realloc_tab(tab_r, 2, true);
		tab_r[j++] = ft_strdup(" ");
	}
	else if ((lst_data->here_doc && lst_data->here_doc_vrai
			&& lst_data->is_pipe))
	{
		tab_r = ft_realloc_tab(tab_r, 2, true);
		tab_r[j++] = ft_strdup("/proc/self/fd/0");
	}
	*start = j;
	return (tab_r);
}

char	**cmd_with_option(char *str, char *path_ok, t_data *lst_data)
{
	char	**tab_return;
	char	*buff;
	int		i;
	int		j;

	i = 2;
	j = 1;
	tab_return = ft_calloc(sizeof(char *), 5);
	tab_return[0] = ft_strdup(path_ok);
	buff = recover_word(str, i++, false);
	if (!ft_strncmp(tab_return[0], "/usr/bin/grep", INT_MAX))
		if_grep();
	while (buff)
	{
		tab_return = ft_realloc_tab(tab_return, 2, true);
		tab_return[j++] = ft_strdup(buff);
		free(buff);
		buff = recover_word(str, i++, false);
	}
	tab_return = push_stdin(tab_return, &j, lst_data);
	tab_return[j] = NULL;
	return (tab_return);
}
