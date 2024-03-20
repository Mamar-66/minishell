/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:07:58 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/20 12:02:35 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <valgrind/valgrind.h>

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	add_signal();
	char	*prompt;
	prompt = return_pwd();
	readline(prompt);
	free(prompt);
	return (1);
}
