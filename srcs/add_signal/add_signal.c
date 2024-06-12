/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:36:08 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/10 18:10:35 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

void	ft_change_numsignal(t_data *lst_data)
{
	if (g_global_numsignal == 130)
	{
		lst_data->status = 130;
		g_global_numsignal = 0;
	}
}

static void	gest_signal(int numsignal)
{
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		if (g_global_numsignal == -10)
		{
			close(STDIN_FILENO);
			printf("\n");
			g_global_numsignal = 130;
		}
		else if (numsignal == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_global_numsignal = 130;
		}
	}
}

static void	gest_ctrl_d(t_data *lst_data)
{
	printf("exit\n");
	freeverithing(lst_data);
	exit (0);
}

char	*add_signal_plus_return_result_prompt(t_data *lst_data)
{
	char				*resul_prompt;

	resul_prompt = "";
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		perror("signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
	signal(SIGINT, gest_signal);
	resul_prompt = get_result_prompt();
	if (resul_prompt == NULL)
		gest_ctrl_d(lst_data);
	add_history(resul_prompt);
	return (resul_prompt);
}
