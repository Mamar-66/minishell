/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/27 12:48:08 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char *str)
{
	char	*opt;
	bool	if_option;

	if_option = false;
	opt = recover_word(str, 2);
	if (ft_strncmp(opt, "-n", 2) == 0)
		if_option = true;
	if (!if_option)
		printf("%s\n", str);
	else
		printf("%s", str);
	free(opt);
}
