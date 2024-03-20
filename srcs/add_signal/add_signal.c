/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:36:08 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/20 12:55:59 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

void	gest_signal(int numsignal)
{
	if (numsignal == SIGINT)
		printf("^C\n");
}

void	add_signal(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = &gest_signal;
	sigaction(SIGINT, &action, NULL);
}
