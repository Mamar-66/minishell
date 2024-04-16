/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:07:57 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/17 00:15:10 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char *wait_for_the_symbole_suite(char *all_str)
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
	str_return = ft_strdup(all_str);
	free(all_str);
	return (str_return);
}

static char	*single_quote_suite(char *str)
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

char	*single_quote(char *str, char sym, int *val_ptr)
{
	char	*str_return;
	char	*first_str;
	char	*first_ptr;
	char	*seconde_ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	first_ptr = ft_strchr(str, sym);
	while (&str[i] != first_ptr && str[i])
		i++;
	first_str = malloc(sizeof(char) * i + 1);
	if (!first_str)
		return (NULL);
	ft_strlcpy(first_str, str, i + 1);
	seconde_ptr = ft_strchr(str + ++i, sym);
	while (&str[i] != seconde_ptr && str[i])
	{
		j++;
		i++;
	}
	str_return = malloc(sizeof(char) * j + 3);
	if (!str_return)
		return (NULL);
	ft_strlcpy(str_return, str + (i - j - 1), j + 3);
	str_return = single_quote_suite(str_return);
	first_str = ft_strjoin(first_str, str_return);
	*val_ptr += ft_strlen(first_str);
	free(str_return);
	return (first_str);
}
