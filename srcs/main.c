/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:58 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/24 11:04:09 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	lst_data;
	char	*readlin_recover;

	lst_data.status = -1;
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		readlin_recover = add_signal_plus_return_result_prompt(&lst_data);
		printf("avant = %s\n", readlin_recover);
		readlin_recover = parsing(readlin_recover, &lst_data);
		printf("apres = %s\n", readlin_recover);
		gest_readline_recover(readlin_recover, &lst_data);
		free(readlin_recover);
	}
	return (1);
}
