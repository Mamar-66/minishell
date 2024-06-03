/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 07:52:31 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/30 15:48:58 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	gest_status_waitpid(int status, t_data *lst_data)

static int	ex_child(char *str_traitement, t_data *lst_data,
	int *pipe_fd, char **tab_free, char **tab_free_dup)
{
	close(pipe_fd[0]);
	if (ft_strncmp(str_traitement, "bash", 5) == 0)
		dup2(pipe_fd[1], lst_data->fd_saved_std_out);
	else if (ft_strchr(str_traitement, '/'))
		dup2(pipe_fd[1], lst_data->fd_saved_std_out);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	gest_readline_recover(str_traitement, lst_data);
	my_free_tab(tab_free);
	my_free_tab(tab_free_dup);
	freeverithing(lst_data);
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
	exit_status = WEXITSTATUS(statu);
	lst_data->status = exit_status;
	return (true);
}

bool	ft_ex(char *str_traitement, t_data *lst_data,
	char **tab_free, char *str, char **tab_free_dup)
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
		free(str);
		ex_child(str_traitement, lst_data, pipe_fd, tab_free, tab_free_dup);
	}
	else
	{
		ex_father(lst_data, pipe_fd, child_pid);
	}
	return (true);
}
