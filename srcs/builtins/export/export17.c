/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export17.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:02:55 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 14:02:57 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	parse_string_suite(t_pars *p, char **str)
{
	if (*str[0] == ' ')
	{
		p->start = ++(*str);
		--(*str);
	}
	else
		p->start = (*str);
	(*str)++;
	while (**str && (!ft_isspace((unsigned char)**str) || p->in_quotes))
	{
		if (**str == p->quote_char)
		{
			p->in_quotes = !p->in_quotes;
			p->quote_char = '\0';
		}
		else if ((**str == '\'' || **str == '"') && !p->in_quotes)
		{
			p->quote_char = **str;
			p->in_quotes = !p->in_quotes;
		}
		(*str)++;
	}
}

void	parse_string_s(t_pars *p, char **str)
{
	if (**str == '\'' || **str == '"')
	{
		p->quote_char = **str;
		p->in_quotes = !p->in_quotes;
		(*str)++;
	}
}

void	ft_unsetbi(char *str, t_data *env)
{
	int		i;
	int		j;
	char	*t;

	j = 0;
	if (no_quote(str) == 0)
		str = changeles(str, '"');
	else
		str = changeles(str, '\'');
	if (str)
	{
		i = 0;
		while (env->tenv[i])
		{
			if (ft_stcmp(str, env->tenv[i], ft_strlen(str)) == 0)
			{
				deletebis(i, env);
			}
			i++;
		}
		t = ft_calloc(sizeof(char), ft_strlen(env->t) + 5);
		ft_strlcpy(t, env->t, INT_MAX);
		env->t = deletes_for_no_mess(str, t, j, env);
	}
}
