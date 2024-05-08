/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:51:40 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/08 12:43:10 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	gest_ctrl_d(t_data *lst_data)
{
	printf("exit\n");
	lst_data->status = 0;
	exit (0);
}

char	*return_prompt(t_data *lst_data)
{
	char	*resul_prompt;
	// int		tmp_fd;

	// tmp_fd = dup(STDIN_FILENO);
	// dup2(STDIN_FILENO, lst_data->fd_saved_std_in);
	resul_prompt = get_result_prompt();
	if (resul_prompt == NULL)
		gest_ctrl_d(lst_data);
	add_history(resul_prompt);
	// dup2(STDIN_FILENO, tmp_fd);
	return (resul_prompt);
}