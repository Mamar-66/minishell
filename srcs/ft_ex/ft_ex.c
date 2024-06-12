/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:52:31 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/12 15:07:50 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	gest_status_waitpid(int status, t_data *lst_data)

static int	ex_child(char **tab_ex, t_data *lst_data,
	int *pipe_fd)
{
	close(pipe_fd[0]);
	if (ft_strncmp(tab_ex[0], "bash", 5) == 0)
		dup2(pipe_fd[1], lst_data->fd_saved_std_out);
	else if (ft_strchr(tab_ex[0], '/'))
		dup2(pipe_fd[1], lst_data->fd_saved_std_out);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	gest_readline_recover(tab_ex[0], lst_data, tab_ex[2]);
	freeverithing(lst_data);
	my_free_tab(tab_ex);
	exit (lst_data->status);
}

static	bool	ex_father(t_data *lst_data, int *pipe_fd, int child_pid)
{
	int	statu;
	int	exit_status;

	(void)lst_data;
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("(dup2(pipe_fd[0], STDIN_FILENO)");
		return (false);
	}
	close(pipe_fd[0]);
	waitpid(child_pid, &statu, 0);
	lst_data->status_for_pipe = statu;
	exit_status = WEXITSTATUS(statu);
	lst_data->status = exit_status;
	unlink(" ");
	return (true);
}

// tab_ex[0] = tab_arm_pipe[i] (str_traitement)
// tab_ex[1] = readlin_recover (str)
// tab_ex[2] = dup_tab[i]      (reel)
bool	ft_ex(char **tab_ex, t_data *lst_data,
			char **tab_free, char **tab_free_dup)
{
	pid_t	child_pid;
	int		pipe_fd[2];

	lst_data->mod_lectur_for_read_final = true;
	if (pipe(pipe_fd) == -1)
		perror("error pipe ");
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("error child_pid ");
		return (false);
	}
	else if (child_pid == 0)
	{
		my_free_tab(tab_free);
		my_free_tab(tab_free_dup);
		ex_child(tab_ex, lst_data, pipe_fd);
	}
	else
	{
		ex_father(lst_data, pipe_fd, child_pid);
	}
	return (true);
}
