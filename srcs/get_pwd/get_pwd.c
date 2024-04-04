/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:01:26 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/04 16:07:48 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_pwd(void)
{
	char	*tab_prompt[4];
	char	*return_pwd;
	int		i;

	i = 0;
	return_pwd = ft_strdup("\033[1;32m  (\033[0m\033[1;34m");
	tab_prompt[0] = getenv("LOGNAME");
	tab_prompt[1] = "\033[0m\033[1;32m)-[\033[0m";
	tab_prompt[2] = getenv("PWD");
	tab_prompt[3] = "\033[1;32m] \033[0m";
	while (i < 4)
		return_pwd = ft_strjoin(return_pwd, tab_prompt[i++]);
	return (return_pwd);
}
