/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:06:37 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/05 14:02:33 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	av_ex(char *str)
{
	int	i;

	i = 0;
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

// bool	*ordre(char **tab)
// {
// 	bool	*tab_return;
// 	int		j;

// 	j = 0;
// 	while (tab[j])
// 		j++;
// 	tab_return = ft_calloc(sizeof(bool), j + 1);
// 	if (!tab_return)
// 		return (NULL);
// 	j = -1;
// 	while (tab[++j])
// 	{
// 		if (ft_strchr(tab[j], '>'))
// 			tab_return[j] = false;

// 	}

	
// 	return (tab_return);
// }
