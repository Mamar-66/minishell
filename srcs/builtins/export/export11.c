/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:26:28 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 10:26:30 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*modify_string(const char *input, char *str)
{
	t_exp	*exp;
	char	*temp;

	exp = malloc(sizeof(t_exp));
	initialise(exp, input);
	while (exp->i < exp->length)
	{
		exp->current = input[exp->i];
		handles_quotes(exp->current, &exp->inside_quotes, &exp->quote_char);
		process_space(exp);
		exp->i++;
	}
	exp->result[exp->j] = '\0';
	temp = ft_strdup(exp->result);
	free(exp->result);
	free(exp);
	free(str);
	free((char *)input);
	return (temp);
}

int	no_quote_bis(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			a = i;
		}
		if (str[i] == '"')
			return (a);
		i++;
	}
	return (0);
}

char	*create_space(char *str, char *temp)
{
	int		i;
	int		j;
	int		a;
	char	*t;

	t = ft_calloc(sizeof(char), ft_strlen(temp) + 100);
	i = 0;
	j = 0;
	a = 0;
	while (str[i])
	{
		while (temp[j] && temp[j] != ' ')
			j++;
		if (str[i] && str[i] == ' ')
		{
			t = create_suite(j, temp, a, t);
			i++;
		}
		t[a] = str[i];
		i++;
		a++;
	}
	free(str);
	return (t);
}

char	*place_quote(char *str, char *temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (temp[j])
		j++;
	while (temp[j] == str[i])
	{
		if (str[i] == '"')
			break ;
		i--;
		j--;
	}
	i++;
	while (temp[j])
	{
		str[i] = temp[j];
		i++;
		j++;
	}
	return (str);
}

void	free_parsed_string(char **parsed)
{
	int	i;

	i = 0;
	while (parsed[i] != NULL)
	{
		free(parsed[i]);
		i++;
	}
	free(parsed);
}
