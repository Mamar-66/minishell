/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:36:08 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/22 12:31:03 by omfelk           ###   ########.fr       */
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
	signal(SIGINT, gest_signal);
		// lst_data->status = 130;
	resul_prompt = get_result_prompt();
	if (resul_prompt == NULL)
		gest_ctrl_d(lst_data);
	add_history(resul_prompt);
	return (resul_prompt);
}
