/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:08:56 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/26 17:23:33 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*first_word(char *str, int *start)
{
	char	*return_word;
	int		i;
	int		j;

	i = *start;
	j = 0;
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10 || str[i] == 13) && str[i])
		i++;
	while (str[i] > 32 && str[i] < 127 && str[i])
	{
		i++;
		j++;
	}
	return_word = malloc(sizeof(char) * j + 1);
	if (!return_word)
		return (NULL);
	ft_strlcpy(return_word, (str + (i - j)), j + 1);
	*start = i;
	return (return_word);
}

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
