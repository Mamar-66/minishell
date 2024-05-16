/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_ft_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:24:24 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/16 11:57:50 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char	**tab_env, char *str_chrch)
{
	char	*str_return;
	int		i;

	i = 0;
	while (tab_env[i])
	{
		if (ft_strncmp(tab_env[i], str_chrch, ft_strlen(str_chrch)) == 0)
			break ;
		i++;
	}
	if (tab_env[i])
		str_return = tab_env[i] + ft_strlen(str_chrch) + 1;
	else
		str_return = "";
	return (str_return);
}
