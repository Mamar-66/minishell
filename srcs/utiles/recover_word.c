/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:08:56 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/01 18:42:03 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char *if_symbole(char *str, char symbol)
// {
// 	char	*str_return;
// 	int		i;

// 	i = 0;
// 	while (str[i] && str[i] != symbol)
// 		i++;
// 	str_return = malloc(sizeof(char) * i + 1);
// 	if (!str_return)
// 		return (NULL);
// 	ft_strlcpy(str_return, str, i + 1);
// 	return (str_return);
// }

static char	*first_word(char *str, int *start)
{
	char	*return_word;
	char	symbol;
	int		i;
	int		j;

	i = *start;
	j = 0;
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
			|| str[i] == 13) && str[i])
		i++;
	symbol = str[i];
	if (symbol == '\'' || symbol == '"')
		while (str[++i] && str[i] != symbol)
			j++;
	else
		while (str[i] > 32 && str[i] < 127 && str[i++])
			j++;
	return_word = malloc(sizeof(char) * j + 1);
	if (!return_word)
		return (NULL);
	ft_strlcpy(return_word, (str + (i - j)), j + 1);
	*start = i;
	return (return_word);
}

/*
	return word 
*/
char	*recover_word(char	*str, unsigned int word_location)
{
	char			*return_word;
	unsigned int	nb;
	int				i;

	i = 0;
	nb = 0;
	return_word = NULL;
	if (word_location == 0 || str[i] == '\0')
		return (NULL);
	while (str[i] && nb < word_location)
	{
		if (return_word)
			free(return_word);
		return_word = first_word(str, &i);
		nb++;
	}
	return (return_word);
}

/*
	move the pointeur; 
*/
int	recover_word_plus_return_position(char	*str,
	unsigned int word_location)
{
	char			*return_word;
	unsigned int	nb;
	int				i;

	i = 0;
	nb = 0;
	return_word = NULL;
	if (word_location == 0 || str[i] == '\0')
		return (-1);
	while (str[i] && nb < word_location)
	{
		if (return_word)
			free(return_word);
		return_word = first_word(str, &i);
		nb++;
	}
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
		|| str[i] == 13) && str[i])
		i++;
	return (i);
}
