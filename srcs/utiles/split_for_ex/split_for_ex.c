/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:03:05 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/10 16:32:56 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	bool	verif_fin_pipe(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i] == ' ' || str[i] == '	')
		i++;
	if ((str[i] > 32 && str[i] <= 127) || str[i] == '\0')
		return (true);
	return (false);
}

static	bool	if_finish(char *str)
{
	int	i;

	i = 1;
	while (str[i] == ' ')
		i++;
	if (!str[i])
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	return (true);
}

static	bool	cnt_pipe(char *str, int *cmp_pipe)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	*cmp_pipe = *cmp_pipe + 1;
	while (str[i])
	{
		if (str[i] == '|')
		{
			cnt++;
			if (!if_finish(str + i))
				return (false);
		}
		if (str[i] > 32 && str[i] < 127 && str[i] != '|')
			break ;
		i++;
	}
	if (cnt > 1)
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
			if (!cnt_pipe(str + i, &cpm_pipe))
				return (-1);
			str[i] = 127;
		}
	}
	return (cpm_pipe);
}

char	**split_for_ex_pipe(char *str, t_data *lst_data)
{
	char	**tab_return;
	int		i;

	i = count_pipe_reel(str);
	if (i == -1)
		return (free(str), NULL);
	tab_return = ft_split(str, 127);
	if (!tab_return)
		return (free(str), NULL);
	if (!verif_fin_pipe(tab_return[i]))
	{
		lst_data->status = 2;
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (my_free_tab(tab_return), free(str), NULL);
	}
	free(str);
	return (tab_return);
}
