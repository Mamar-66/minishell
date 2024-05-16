/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:36:08 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/11 11:09:14 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

static void	gest_signal(int numsignal)
{
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		if (numsignal == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (numsignal == SIGQUIT)
		{
			printf("sigquit\n");
		}
	}
}

static void	gest_ctrl_d(t_data *lst_data)
{
	printf("exit\n");
	freeverithing(lst_data);
	lst_data->status = 0;
	exit (0);
}

char	*add_signal_plus_return_result_prompt(t_data *lst_data)
{
	struct sigaction	action;
	char				*resul_prompt;

	resul_prompt = "";
	ft_bzero(&action, sizeof(action));
	action.sa_handler = &gest_signal;
	if (sigaction(SIGCHLD, &action, NULL) == -1)
		perror("SIGCHLD");
	if (sigaction(SIGINT, &action, NULL) == -1)
		perror("SIGINT");
	if (sigaction(SIGQUIT, &action, NULL) == -1)
		perror("signal");
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		perror("signal");
	resul_prompt = get_result_prompt();
	if (resul_prompt == NULL)
		gest_ctrl_d(lst_data);
	add_history(resul_prompt);
	return (resul_prompt);
}

	// sigemptyset(&action.sa_mask);
	// sigaddset(&action.sa_mask, SIGQUIT);
	//sigaddset(&action.sa_mask, SIGINT);
	//sigaddset(&action.sa_mask, SIGTERM);