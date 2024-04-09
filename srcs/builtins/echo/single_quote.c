/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:07:57 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/09 14:20:00 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char 	*wait_for_the_symbole_suite(char *all_str)
{
	char	*buff;
	char	*str_return;

	buff = readline("quote > ");
	str_return = ft_strjoin(all_str, "\n");
	str_return = ft_strjoin(str_return, buff);
	str_return = ft_strjoin(str_return, "\0");
	free(buff);
	return (str_return);
}

static char	*wait_for_the_symbole(char *str)
{
	char	*all_str;
	// char	*pre_str_return;
	char	*str_return;
	int		i;

	i = 0;
	all_str = ft_strdup(str);
	while (all_str[i] != '\'' && all_str[i])
		i++;
	all_str[i] = 127;
	while (ft_strchr(all_str, '\'') == NULL)
		all_str = wait_for_the_symbole_suite(all_str);
	while (all_str[i] != '\'' && all_str[i])
		i++;
	all_str[i] = 127;
	// pre_str_return = ft_strldup(all_str, ft_strlen(all_str) - i);
	// if (ft_strchr(all_str, '\''))
	// 	pre_str_return = ft_strjoin(pre_str_return, all_str + i + 1);
	// str_return = ft_strdup(pre_str_return);
	str_return = ft_strdup(all_str);
	free(all_str);
	// free(pre_str_return);
	return (str_return);
}

char	*single_quote(char *str)
{
	char	*str_return;

	if (ft_strchr(str, '\''))
		str_return = wait_for_the_symbole(str);
	else if (((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')))
		str_return = recover_word(str, 1, true);
	else
		perror("error single quote\n");
	free(str);
	return (str_return);
}
