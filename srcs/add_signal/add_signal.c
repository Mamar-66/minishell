/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:36:08 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/26 15:33:17 by omfelk           ###   ########.fr       */
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
	lst_data->status = 0;
	exit (1);
}

char	*add_signal_plus_return_result_prompt(t_data *lst_data)
{
	struct sigaction	action;
	char				*resul_prompt;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = &gest_signal;
	if (sigaction(SIGINT, &action, NULL) == -1)
		perror("SIGINT");
	if (sigaction(SIGQUIT, &action, NULL) == -1)
		perror("SIGQUIT");
	resul_prompt = get_result_prompt();
	if (resul_prompt == NULL)
		gest_ctrl_d(lst_data);
	return (resul_prompt);
}

	// sigemptyset(&action.sa_mask);
	// sigaddset(&action.sa_mask, SIGQUIT);
	//sigaddset(&action.sa_mask, SIGINT);
	//sigaddset(&action.sa_mask, SIGTERM);