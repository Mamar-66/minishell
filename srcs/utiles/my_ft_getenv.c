/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_ft_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:24:24 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/07 18:26:04 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	size_t	tail_var(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*ft_getenv(char	**tab_env, char *str_chrch)
{
	char	*str_return;
	int		i;
	char	c[2];

	i = 0;
	c[0] = 127;
	c[1] = '\0';
	while (tab_env[i])
	{
		if (ft_strncmp(tab_env[i], str_chrch, ft_strlen(str_chrch)) == 0
			&& tail_var(tab_env[i]) == ft_strlen(str_chrch))
			break ;
		i++;
	}
	if (tab_env[i])
		str_return = ft_strdup(tab_env[i] + ft_strlen(str_chrch) + 1);
	else
		str_return = ft_strdup(c);
	return (str_return);
}
