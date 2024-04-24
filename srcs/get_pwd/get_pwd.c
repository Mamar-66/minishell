/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:01:26 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/24 10:33:35 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	return juste string of pwd
*/
char	*return_str_pwd(void)
{
	char	buff[255];

	if (!getcwd(buff, sizeof(buff)))
		perror("pwd buff size is small\n");
	return (ft_strdup(buff));
}
/*
	for display
*/

char	*return_pwd(void)
{
	char	*tab_prompt[4];
	char	*return_pwd;
	char	*pwd;
	int		i;

	i = 0;
	return_pwd = ft_strdup("\033[1;32m  (\033[0m\033[1;34m");
	tab_prompt[0] = getenv("LOGNAME");
	tab_prompt[1] = "\033[0m\033[1;32m)-[\033[0m";
	pwd = return_str_pwd();
	while (pwd[i])
		i++;
	while (pwd[i] != '/')
		i--;
	tab_prompt[2] = ft_strdup(pwd + ++i);
	tab_prompt[3] = "\033[1;32m] \033[0m";
	i = 0;
	while (i < 4)
		return_pwd = ft_strjoin(return_pwd, tab_prompt[i++]);
	free(tab_prompt[2]);
	free(pwd);
	return (return_pwd);
}
