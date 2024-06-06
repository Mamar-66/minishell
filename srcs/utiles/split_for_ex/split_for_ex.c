/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:05 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/06 17:59:36 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	bool	verif_fin_pipe(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] == ' ')
		i++;
	if (str[i] > 32 && str[i] <= 127)
		return (true);
	return (false);
}

static	bool	cnt_pipe(char *str)
{
	int	i;
	int	cnt_pipe;

	i = 0;
	cnt_pipe = 0;
	while (str[i])
	{
		if (str[i] == '|')
			cnt_pipe++;
		if (cnt_pipe > 0 && str[i] > 32 && str[i] < 127)
			break ;
		i++;
	}
	if (cnt_pipe > 1)
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	return (true);
}

static	int	count_pipe_reel(char *str)
{
	int		i;
	int		cpm_pipe;

	i = -1;
	cpm_pipe = 0;
	while (str[++i])
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
	int		i;

	if (!cnt_pipe(str))
		return (free(str), NULL);
	i = count_pipe_reel(str);
	tab_return = ft_split(str, 127);
	if (!tab_return)
		return (NULL);
	if (!verif_fin_pipe(tab_return[i]))
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (my_free_tab(tab_return), free(str), NULL);
	}
	free(str);
	return (tab_return);
}
