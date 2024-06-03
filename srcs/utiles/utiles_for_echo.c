/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_for_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:28:04 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/24 10:31:29 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	free(return_word);
	return (i);
}

bool	verif_n(char *opt)
{
	size_t	i;

	i = 0;
	if (opt[0] == '-')
		i++;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
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
	while (verif_n(opt))
	{
		free(opt);
		i++;
		opt = recover_word(str, i, false);
		if (!opt)
		{
			free(opt);
			return (-1);
		}
	}
	*pos_start = i;
	free(opt);
	return (++i);
}
