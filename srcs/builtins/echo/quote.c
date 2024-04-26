/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:07:57 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/17 20:26:07 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//static	char	*wait_for_the_symbole_suite(char *all_str, bool dquote)
//{
//	char	*buff;
//	char	*str_return;

//	if (dquote)
//		buff = readline("dquote > ");
//	else
//		buff = readline("quote > ");
//	str_return = ft_strjoin(all_str, "\n");
//	str_return = ft_strjoin(str_return, buff);
//	str_return = ft_strjoin(str_return, "\0");
//	free(buff);
//	return (str_return);
//}

//static char	*wait_for_the_symbole(char *str, char sym, bool dquote)
//{
//	char	*all_str;
//	char	*str_return;
//	int		i;

//	i = 0;
//	all_str = ft_strdup(str);
//	while (all_str[i] != sym && all_str[i])
//		i++;
//	all_str[i] = 127;
//	while (ft_strchr(all_str, sym) == NULL)
//		all_str = wait_for_the_symbole_suite(all_str, dquote);
//	while (all_str[i] != sym && all_str[i])
//		i++;
//	all_str[i] = 127;
//	str_return = ft_strdup(all_str);
//	free(all_str);
//	return (str_return);
//}

//static char	*quote_suite(char *str, char sym, bool dquote)
//{
//	char	*str_return;

//	if (ft_strchr(str, sym))
//		str_return = wait_for_the_symbole(str, sym, dquote);
//	else if (((str[0] == sym && str[ft_strlen(str) - 1] == sym)))
//		str_return = recover_word(str, 1, true);
//	else
//		perror("error single quote\n");
//	free(str);
//	return (str_return);
//}

//char	*quote(char *str, t_data *lst_data, char sym, bool dquote)
//{
//	char	*str_return;
//	char	*first_str;
//	char	*first_ptr;
//	char	*seconde_ptr;
//	int		count[2];

//	count[0] = 0;
//	count[1] = 0;
//	first_ptr = ft_strchr(str, sym);
//	while (&str[count[0]] != first_ptr && str[count[0]])
//		count[0]++;
//	first_str = malloc(sizeof(char) * count[0] + 1);
//	if (!first_str)
//		return (NULL);
//	ft_strlcpy(first_str, str, count[0] + 1);
//	seconde_ptr = ft_strchr(str + ++count[0], sym);
//	while (&str[count[0]] != seconde_ptr && str[count[0]])
//	{
//		count[1]++;
//		count[0]++;
//	}
//	str_return = malloc(sizeof(char) * count[1] + 3);
//	if (!str_return)
//		return (NULL);
//	ft_strlcpy(str_return, str + (count[0] - count[1] - 1), count[1] + 3);
//	str_return = quote_suite(str_return, sym, dquote);
//	first_str = ft_strjoin(first_str, str_return);
//	if (dquote)
//		first_str = double_quote(first_str, lst_data);
//	free(str_return);
//	return (first_str);
//}

char	*quote(char *str, t_data *lst_data)
{
	char	*return_str;

	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return_str = ft_strldup(str + 1, 1);
	else if (str[0] == '"' && str[ft_strlen(str) - 1] == '"') 
		return_str = double_quote(ft_strldup(str + 1, 1), lst_data);
	else
		return_str = NULL;
	if (!return_str && str[0] == '\'')
		printf("error argument simple quote\n");
	else if (!return_str && str[0] == '"')
		printf("error argument double quote\n");
	return (return_str);
}
