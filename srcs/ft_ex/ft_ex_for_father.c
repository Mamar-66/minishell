/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_for_father.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:11:40 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/14 13:52:11 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ex_child(char *str_traitement, t_data *lst_data, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], lst_data->fd_saved_std_out) == -1)
	{
		perror("error <dup2(pipe_fd[1], STDOUT_FILENO)> ");
		return (false);
	}
	close(pipe_fd[1]);
	if (!ft_pipex(str_traitement, lst_data))
		return (false);
	return (true);
}

static	bool	ex_father(t_data *lst_data, int *pipe_fd, int child_pid)
{
	(void)lst_data;
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("(dup2(pipe_fd[0], STDIN_FILENO)");
		return (false);
	}
	close(pipe_fd[0]);
	waitpid(child_pid, NULL, 0);
	return (true);
}

bool	ft_ex_father(char *str_traitement, t_data *lst_data)
{
	pid_t	child_pid;
	int		pipe_fd[2];
	bool	val;

	lst_data->mod_lectur_for_read_final = true;
	val = false;
	if (pipe(pipe_fd) == -1)
		perror("error pipe ");
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("error child_pid ");
		return (false);
	}
	else if (child_pid == 0)
		val = ex_child(str_traitement, lst_data, pipe_fd);
	else
		ex_father(lst_data, pipe_fd, child_pid);
	if (val)
		return (false);
	return (true);
}
