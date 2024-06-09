/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:26:11 by sbarbe            #+#    #+#             */
/*   Updated: 2024/06/06 10:26:12 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

int	check_dollar_position(const char *input)
{
	int		i;
	bool	inside_single_quotes;
	bool	inside_double_quotes;

	inside_single_quotes = false;
	inside_double_quotes = false;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			inside_single_quotes = !inside_single_quotes;
		else if (input[i] == '"')
			inside_double_quotes = !inside_double_quotes;
		else if (input[i] == '$')
		{
			if (inside_single_quotes)
				return (5);
			else if (inside_double_quotes)
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (1);
}

char	*dollars_parsing(char *str, t_data *env)
{
	int		i;
	int		a;
	int		z;

	i = 0;
	a = 0;
	z = 0;
	env->dolar = 1;
	if (check_dollar_position(str) != 5)
	{
		str = dollars_parsing_suite(str, z, env);
	}
	return (str);
}

char	*copy_section(const char **str, char quote_char)
{
	const char	*start;
	char		*section;
	size_t		len;

	start = *str;
	while (**str && (**str != quote_char
			|| quote_char == '\0' || (*str)[-1] == '\\'))
		(*str)++;
	len = *str - start;
	section = (char *)malloc(len + 1);
	if (!section)
		return (NULL);
	ft_strlcpy(section, start, len);
	section[len] = '\0';
	return (section);
}
