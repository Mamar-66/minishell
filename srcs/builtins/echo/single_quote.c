/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:07:57 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/04 00:55:25 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	wait_for_the_symbole_suite(char *buff, char *all_str)
{
		buff = readline("quote-> ");
		all_str = ft_strjoin(all_str, buff);
		all_str = ft_strjoin(all_str, "\n");
}

static char	*wait_for_the_symbole(char *str)
{
	char	*all_str;
	char	buff;
	char	*pre_str_return;
	char	*str_return;
	int		i;

	i = 0;
	all_str = ft_strdup(str + 1);
	all_str = ft_strjoin(all_str, "\n");
	while (1)
	{
		if (ft_strchr(all_str, str[0]) != NULL)
			break;
		wait_for_the_symbole_suite(&buff, all_str);
	}
	while (all_str[i] != str[0])
		i++;
	pre_str_return = ft_strldup(all_str, ft_strlen(all_str) - i);
	if (all_str[i + 1])
		pre_str_return = ft_strjoin(pre_str_return, all_str + i + 1);
	str_return = ft_strdup(pre_str_return);
	free(all_str);
	free(pre_str_return);
	return (str_return);
}

//static char	*single_quote_ok(char *str)
//{
//	char	*str_return;

//	str_return = ft_strdup(str + 1);
//	str_return[ft_strlen(str_return) - 1] = '\0';
//	printf("ok\n");
//	return (str_return);
//}

char	*single_quote(char *str)
{
	char	*str_return;

	if (((str[0] == '\'' && str[ft_strlen(str) - 1] != '\'')))
		str_return = wait_for_the_symbole(str);
	else if (((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')))
		str_return = recover_word(str, 1, true);
	else
		perror("error single quote\n");
	free(str);
	return (str_return);
}
