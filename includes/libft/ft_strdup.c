/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:11:07 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/09 08:29:49 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_text;
	size_t	i;

	i = ft_strlen(s) + 1;
	new_text = (char *) malloc((sizeof(char) * i));
	if (new_text == NULL)
		return (NULL);
	ft_strlcpy(new_text, s, i);
	return (new_text);
}
