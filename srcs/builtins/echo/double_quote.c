/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:11:45 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/04 12:11:55 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char 	*wait_for_the_symbole_suite(char *all_str)
{
	char	*buff;
	char	*str_return;

	buff = readline("quote > ");
	str_return = ft_strjoin(all_str, buff);
	str_return = ft_strjoin(str_return, "\n\0");
	free(buff);
	return (str_return);
}

static char	*wait_for_the_symbole(char *str)
{
	char	*all_str;
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
		all_str = wait_for_the_symbole_suite(all_str);
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

static char	*gest_global_var(char *str)
{
	char	*str_return;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			if (ft_isalpha(str[i]) || str[i] == '_')
				j++;
			else
				break;
	}
	free(str);
	return (str_return);
}

char	*double_quote(char *str)
{
	char	*str_return;

	if (((str[0] == '"' && str[ft_strlen(str) - 1] != '"')
			|| (str[0] == '"' && ft_strlen(str) - 1 == 0)))
		str_return = wait_for_the_symbole(str);
	else if (((str[0] == '"' && str[ft_strlen(str) - 1] == '"')))
		str_return = recover_word(str, 1, true);
	else
		perror("error double quote\n");
	str_return = gest_global_var(str_return);
	free(str);
	return (str_return);
}
