/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:06:37 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/11 15:14:16 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	bool	count_sym(char *str, char sym)
{
	int	i;
	int	ss;

	i = 0;
	ss = 0;
	while (str[i])
	{
		if (str[i] == sym)
			ss++;
		i++;
	}
	if (ss % 2 != 0)
	{
		while (str[i] != sym)
			i--;
		printf("error argument simple quote <%s>\n", str + i);
		return (false);
	}
	return (true);
}

static	bool	if_all_space(char *str)
{
	int	i;
	int	d;
	int	s;

	i = 0;
	d = 0;
	s = 0;
	if (!ft_strchr(str, '"') && !ft_strchr(str, '\''))
		return (true);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '"' && str[i] != '\'')
			return (true);
		if (str[i] == '"')
			d++;
		if (str[i] == '\'')
			s++;
		if (s > 1 || d > 1)
			break ;
		i++;
	}
	write(1, str + 1, i - 1);
	write(1, " \x1b[31m: command not found\x1b[0m\n",
		ft_strlen(" \x1b[31m: command not found\x1b[0m\n"));
	return (false);
}

bool	av_ex(char *str)
{
	int	i;

	i = 0;
	if (!count_sym(str, '"') || !count_sym(str, '\'') || !if_all_space(str))
		return (false);
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
			|| str[i] == 13) && str[i])
		i++;
	if (str[i] == '|')
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	return (true);
}

void	affiche_in_terminal(t_data *lst_data,
	char *readline_recover, char **tab_arm_pipe)
{
	char	buff[25555];

	ft_bzero(buff, 25555);
	if (lst_data->mod_lectur_for_read_final && readline_recover[0]
		&& tab_arm_pipe[0])
	{
		read(STDIN_FILENO, buff, 25555);
		printf("%s", buff);
	}
}
