/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:09:22 by sbarbe            #+#    #+#             */
/*   Updated: 2024/05/15 14:09:24 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*anothersuite(char *b)
{
	if (b)
		free(b);
	b = ft_calloc(sizeof(char), 2);
	b[0] = 'a';
	return (b);
}

void	ft_error_and_status(t_data *en, char *str)
{
	en->status = 1;
	printf("minishelle: export: `%s\': not a valid identifier\n", str);
}
