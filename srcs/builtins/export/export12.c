/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:37:26 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 10:37:27 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**parse_string(char *str)
{
	t_pars	p;

	initialise_pars(&p, str);
	while (*str)
	{
		while (ft_isspace((unsigned char)*str) && !p.in_quotes)
			str++;
		parse_string_s(&p, &str);
		if (*str && (!ft_isspace((unsigned char)*str) || p.in_quotes))
		{
			--str;
			parse_string_suite(&p, &str);
			p.len = str - p.start;
			p.section = (char *)malloc(p.len + 1);
			if (!p.section)
				return (NULL);
			ft_strlcpy(p.section, p.start, p.len + 1);
			p.section[p.len] = '\0';
			p.result[p.index++] = p.section;
		}
	}
	p.result[p.index] = NULL;
	return (p.result);
}

int	no_quote(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '"')
				return (0);
			if (str[i] == '\'')
				return (5);
			i++;
		}
	}
	return (1);
}

int	how_quote(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == '"')
			a++;
		i++;
	}
	return (a);
}
