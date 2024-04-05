/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:08:56 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/05 16:54:58 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	first_word_plus(char *str, int *start ,int *cmp)
{
	char	symbol;
	int		i;
	int		j;

	i = *start;
	j = *cmp;
	symbol = str[i];
	if (symbol == '\'' || symbol == '"')
		while (str[i])
		{
			i++;
			if (str[i] == symbol)
			{
				j += 2;
				i++;
				break ;
			}
			j++;
		}
	else
		while (str[i] > 32 && str[i] < 127 && str[i++])
			j++;
	*start = i;
	*cmp = j;
}

/*
	return first word
	mod (if it's false there are the quotes)
*/
static char	*first_word(char *str, int *start, bool mod)
{
	char	*return_word;
	int		i;
	int		j;

	i = *start;
	j = 0;
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
			|| str[i] == 13) && str[i])
		i++;
	first_word_plus(str, &i, &j);
	if (mod)
	{
		j -= 2;
		i -= 1;
	}
	return_word = malloc(sizeof(char) * j + 1);
	if (!return_word)
		return (NULL);
	ft_strlcpy(return_word, (str + (i - j)), j + 1);
	*start = i;
	return (return_word);
}

/*
	return word
	mod (if it's false there are the quotes)
*/
char	*recover_word(char	*str, unsigned int word_location, bool mod)
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
		return_word = first_word(str, &i, mod);
		nb++;
	}
	if (nb < word_location)
		return (NULL);
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
		return_word = first_word(str, &i, false);
		nb++;
	}
	while ((str[i] == 32 || str[i] == 9 || str[i] == 10
		|| str[i] == 13) && str[i])
		i++;
	return (i);
}

/*
	pos_strat = index start string 
	return index finish string
*/
int	word_has_print_return_pos_finish(char *str, int *pos_start)
{
	char	*opt;
	int		i;

	i = *pos_start;
	opt = recover_word(str, i, false);
	while (ft_strncmp(opt, "-n", 3) == 0)
	{
		free(opt);
		i++;
		opt = recover_word(str, i, false);
	}
	*pos_start = i;
	free(opt);
	return (++i);
}
