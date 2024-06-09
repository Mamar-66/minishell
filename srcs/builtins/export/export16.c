/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:55:16 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 12:55:18 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handles_quotes(char current, bool *inside_quotes, char *quote_char)
{
	if (current == '"' || current == '\'')
	{
		if (*inside_quotes && current == *quote_char)
			*inside_quotes = false;
		else if (!*inside_quotes)
		{
			*inside_quotes = true;
			*quote_char = current;
		}
	}
}

void	initialise(t_exp *exp, const char *input)
{
	if (input)
		exp->length = ft_strlen(input);
	else
		exp->length = 0;
	exp->result = (char *)malloc(exp->length + 1);
	if (!exp->result)
		return ;
	exp->inside_quotes = false;
	exp->quote_char = '\0';
	exp->j = 0;
	exp->i = 0;
	exp->last_was_space = false;
}

void	process_space(t_exp *exp)
{
	if (exp->current == ' ')
	{
		if (exp->inside_quotes)
			exp->result[exp->j++] = exp->current;
		else
		{
			if (!exp->last_was_space)
			{
				exp->result[exp->j++] = exp->current;
				exp->last_was_space = true;
			}
		}
	}
	else
	{
		exp->result[exp->j++] = exp->current;
		exp->last_was_space = false;
	}
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	initialise_pars(t_pars *p, const char *str)
{
	p->result = NULL;
	p->index = 0;
	p->in_quotes = 0;
	p->quote_char = '\0';
	p->str_len = ft_strlen(str);
	p->result = malloc((p->str_len / 2 + 2) * sizeof(char *));
	if (!p->result)
		return ;
}
