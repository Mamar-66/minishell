/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:01:26 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/18 15:21:11 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



char	*return_pwd(void)
{
	char	*all_pwd;
	char	*return_pwd;
	// char	*av;
	char	*ap;
	int		i;

	i = 0;
	all_pwd = getenv("PWD");
	while (all_pwd[i])
		i++;
	while (all_pwd[i] != '/')
		i--;
	i++;
	ap = ft_strdup(" : ");
	return_pwd = ft_strdup(all_pwd + i);
	return_pwd = ft_strjoin(return_pwd, ap);
	free(ap);
	// free(all_pwd);
	return (return_pwd);
}
