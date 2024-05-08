/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:58 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/08 13:41:56 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all
//  --suppressions=val.supp -s  ./minishell

// static bool	ft_ex(t_data *lst_argv)
// {
// 	pid_t	child_pid;
// 	int		pipe_fd[2];

// 	if (pipe(pipe_fd) == -1)
// 		perror("error pipe ");
// 	child_pid = fork();
// 	if (child_pid == -1)
// 	{
// 		perror("error child_pid ");
// 		return (false);
// 	}
// 	else if (child_pid == 0)
// 		ex_child(lst_argv, pipe_fd);
// 	else
// 		ex_father(lst_argv, pipe_fd, child_pid);
// 	return (true);
// }

// static bool	ex_child(t_data *lst_argv, int	*pipe_fd)
// {
// 	close(pipe_fd[0]);
// 	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 	{
// 		perror("error <dup2(pipe_fd[1], STDOUT_FILENO)> ");
// 		return (false);
// 	}
// 	close(pipe_fd[1]);

// 	return (true);
// }

// bool	ex_father(t_data *lst_argv, int *pipe_fd, int child_pid)
// {
// 	(void)lst_argv;
// 	close(pipe_fd[1]);
// 	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 	{
// 		perror("(dup2(pipe_fd[0], STDIN_FILENO) ");
// 		return (false);
// 	}
// 	close(pipe_fd[0]);
// 	waitpid(child_pid, NULL, 0);
// 	return (true);
// }

static	bool	ft_manager(t_data *lst_data)
{
	char	*readlin_recover;
	char	**tab_arm_pipe;
	int		i;

	while (1)
	{
		i = 0;
		readlin_recover = add_signal_plus_return_result_prompt(lst_data);
		tab_arm_pipe = ft_split(readlin_recover, '|');
		while (tab_arm_pipe[i])
		{
			tab_arm_pipe[i] = parsing(tab_arm_pipe[i], lst_data);
			if (tab_arm_pipe[i])
				gest_readline_recover(tab_arm_pipe[i], lst_data);
			i++;
		}
		my_free_tab(tab_arm_pipe);
	}
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data		lst_data;

	lst_data.status = -1;
	lst_data.fd_saved_std_out = dup(STDOUT_FILENO);
	lst_data.fd_saved_std_in = dup(STDIN_FILENO);
	(void)argc;
	(void)argv;
	(void)env;
	ft_manager(&lst_data);
	return (1);
}
