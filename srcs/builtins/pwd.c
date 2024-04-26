/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:37 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/26 14:34:48 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char *str)
{
	char	*affiche_pwd;
	int 	i;
	bool 	too_many;

	i = 0;
	too_many = false;
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10 || str[i] == 13) && str[i])
	{
		i++;
		if (str[i] > 32 && str[i] < 127)
			too_many = true;
	}
	if (!too_many)
	{
		affiche_pwd = return_str_pwd();
		printf("%s\n", affiche_pwd);
		free(affiche_pwd);
	}
	else
		printf("pwd : too many arguments\n");
}
