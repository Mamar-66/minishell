/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:11:45 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/04 12:11:55 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char 	*wait_for_the_symbole_suite(char *all_str)
{
	char	*buff;
	char	*str_return;

	buff = readline("dquote > ");
	str_return = ft_strjoin(all_str, "\n");
	str_return = ft_strjoin(str_return, buff);
	str_return = ft_strjoin(str_return, "\0");
	free(buff);
	return (str_return);
}

static char	*wait_for_the_symbole(char *str)
{
	char	*all_str;
	char	*str_return;
	int		i;

	i = 0;
	all_str = ft_strdup(str);
	while (all_str[i] != '"' && all_str[i])
		i++;
	all_str[i] = 127;
	while (ft_strchr(all_str, '"') == NULL)
		all_str = wait_for_the_symbole_suite(all_str);
	while (all_str[i] != '"' && all_str[i])
		i++;
	all_str[i] = 127;
	str_return = ft_strdup(all_str);
	free(all_str);
	return (str_return);
}

//static char *val_var(char *str, int *ptr, t_data *lst_data)
//{
//	char	*str_return;
//	char	*var;
//	int		i_j[2];

//	i_j[0] = -1;
//	i_j[1] = 0;
//	if (str[0] == '?')
//	{
//		str_return = ft_strdup(ft_itoa(lst_data->status));
//		return (str_return);
//	}
//	while (str[++i_j[0]])
//		if (ft_isalpha(str[i_j[0]]) || str[i_j[0]] == '_')
//			i_j[1]++;
//		else
//			break ;
//	var = malloc(sizeof(char) * i_j[1] + 1);
//	if (!var)
//		return (NULL);
//	ft_strlcpy(var, str + (i_j[0] - i_j[1]), i_j[1] + 1);
//	str_return = getenv(var);
//	*ptr += i_j[1];
//	free(var);
//	return (str_return);
//}

//static char	*gest_global_var(char *str, t_data *lst_data)
//{
//	char	*str_return;
//	char 	c[1];
//	char 	*var;
//	int 	i;

//	i = -1;
//	c[1] = '\0';
//	str_return = ft_strdup("");
//	while (str[++i])
//	{
//		if (str[i] == '$' && str[i + 1] != '\n')
//		{
//			var = val_var(str + ++i, &i, lst_data);
//			if (var)
//				str_return = ft_strjoin(str_return, var);
//			else
//				str_return = ft_strjoin(str_return, " ");
//		}
//		else
//		{
//			c[0] = str[i];
//			str_return = ft_strjoin(str_return, c);
//		}
//	}
//	return (str_return);
//}

static char	*double_quote_suite(char *str)
{
	char	*str_return;

	if (ft_strchr(str, '"'))
		str_return = wait_for_the_symbole(str);
	else if (((str[0] == '"' && str[ft_strlen(str) - 1] == '"')))
		str_return = recover_word(str, 1, true);
	else
		perror("error single quote\n");
	free(str);
	return (str_return);
}

char	*double_quote(char *str, char sym, int *val_ptr)
{
	char	*str_return;
	char	*first_str;
	char	*first_ptr;
	char	*seconde_ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	first_ptr = ft_strchr(str, sym);
	while (&str[i] != first_ptr && str[i])
		i++;
	first_str = malloc(sizeof(char) * i + 1);
	if (!first_str)
		return (NULL);
	ft_strlcpy(first_str, str, i + 1);
	seconde_ptr = ft_strchr(str + ++i, sym);
	while (&str[i] != seconde_ptr && str[i])
	{
		j++;
		i++;
	}
	str_return = malloc(sizeof(char) * j + 3);
	if (!str_return)
		return (NULL);
	ft_strlcpy(str_return, str + (i - j - 1), j + 3);
	str_return = double_quote_suite(str_return);
	first_str = ft_strjoin(first_str, str_return);
	*val_ptr += ft_strlen(first_str);
	free(str_return);
	return (first_str);
}
