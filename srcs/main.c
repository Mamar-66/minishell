/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:58 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/09 12:25:18 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valgrind --leak-check=full --show-leak-kinds=all
//  --suppressions=val.supp -s  ./minishell

static bool	ex_child(char *str_traitement, t_data *lst_data, int *pipe_fd)
{
 	(void)lst_data;
	(void)str_traitement;

 	close(pipe_fd[0]);
 	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
 	{
 		perror("error <dup2(pipe_fd[1], STDOUT_FILENO)> ");
 		return (false);
 	}
 	close(pipe_fd[1]);
	gest_readline_recover(str_traitement, lst_data);
	// printf("child\n");
	// printf("strr = %s\n", str_traitement);
 	return (true);
}

bool	ex_father(t_data *lst_data, int *pipe_fd, int child_pid)
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
	// printf("father\n");
	return (true);
}

static	bool	ft_ex(char *str_traitement, t_data *lst_data)
{
	(void)lst_data;
 	pid_t	child_pid;
 	int		pipe_fd[2];
	char	*tmp;

	// printf("manager\n");
	// printf("str = %s\n", str_traitement);
	if (pipe(pipe_fd) == -1)
		perror("error pipe ");
 	child_pid = fork();
 	if (child_pid == -1)
 	{
 		perror("error child_pid ");
 		return (false);
 	}
 	else if (child_pid == 0)
 		ex_child(str_traitement, lst_data, pipe_fd);
 	else
 		ex_father(lst_data, pipe_fd, child_pid);
	tmp = get_next_line(STDIN_FILENO);
	printf("recupe = %s\n", tmp);
	free(tmp);
	return (true);
}

static	bool	ft_manager(t_data *lst_data)
{
	char	*readlin_recover;
	char	**tab_arm_pipe;
	int		i;

	// while (1)
	// {
		i = -1;
		readlin_recover = add_signal_plus_return_result_prompt(lst_data);
		tab_arm_pipe = ft_split(readlin_recover, '|');
		while (tab_arm_pipe[++i])
		{
			tab_arm_pipe[i] = parsing(tab_arm_pipe[i], lst_data);
			if (tab_arm_pipe[i])
				ft_ex(tab_arm_pipe[i], lst_data);
		}
		my_free_tab(tab_arm_pipe);
		free(readlin_recover);
	// }
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
