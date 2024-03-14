/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realoc_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:00 by omfelk            #+#    #+#             */
/*   Updated: 2024/01/31 21:11:43 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_tab(char **tab, size_t len)
{
	size_t	j;
	char	**tab_new;

	j = 0;
	while (tab[j])
		j++;
	tab_new = ft_calloc(sizeof(char *), (j + len));
	if (!tab_new)
		return (NULL);
	j = 0;
	while (tab[j] && j <= len)
	{
		tab_new[j] = ft_strdup(tab[j]);
		j++;
	}
	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (tab_new);
}
