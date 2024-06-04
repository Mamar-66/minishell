/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:05 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/04 14:53:11 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// reel is not in double quote
static	int	count_pipe_reel(char *str)
{
	int		i;
	int		cpm_pipe;

	i = -1;
	cpm_pipe = 0;
	while(str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			if (str[i - 1] == '"')
				while (str[i] && str[i] != '"')
					i++;
			else if (str[i - 1] == '\'')
				while (str[i] && str[i] != '\'')
					i++;
		}
		if (str[i] && str[i] == '|')
		{
			str[i] = 127;
			cpm_pipe++;
		}
	}
	return (cpm_pipe);
}

char	**split_for_ex_pipe(char *str)
{
	char	**tab_return;

	count_pipe_reel(str);
	tab_return = ft_split(str, 127);
	free(str);
	return (tab_return);
}
