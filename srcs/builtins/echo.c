/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/02 17:52:39 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*wait_for_end_symbole(char *str)
{
	char	*all_str;
	char	*buff;
	char	*pre_str_return;
	char	*str_return;
	int		i;

	i = 0;
	all_str = ft_strdup(str + 1);
	all_str = ft_strjoin(all_str, "\n");
	while (1)
	{
		if (ft_strchr(all_str, str[0]) != NULL)
			break;
		buff = readline("> ");
		all_str = ft_strjoin(all_str, buff);
		free(buff);
	}
	while (all_str[i] != str[0])
		i++;
	pre_str_return = ft_strldup(all_str, i - 1);
	if (all_str[i])
		pre_str_return = ft_strjoin(pre_str_return, all_str + i + 1);
	str_return = ft_strldup(pre_str_return, 1);
	free(str);
	free(all_str);
	free(pre_str_return);
	return (str_return);
}

/*
	gest symbole " end ' end $
*/

static char	*gest_symbole(char *str, int start, int finish)
{
	(void)finish;
	char	*str_parssing;
	char	*buff;
	int		i;

	i = 1;
	buff = recover_word(str + start, i);
	// printf("\nbuff deb>%c<\n", buff[0]);
	// printf("nb = %ld\n", ft_strlen(buff));
	// printf("buff fin >%c<\n", buff[ft_strlen(buff) - 1]);
	while (buff)
	{
		if (((buff[0] == '\''  && buff[ft_strlen(buff) - 1] != '\'')
			|| (buff[0] == '"'  && buff[ft_strlen(buff) - 1] != '"')))
			buff = wait_for_end_symbole(buff);
		else
			buff = recover_word(str + start, i);
		printf("text %s\n", buff);
		return (NULL);
	}
	// 	else if (str[start] == '\'')
	// 		str_parssing = ft_strldup(str + start + 1, 1);
	// else if (str[start] == '"')
	// {
	// 	printf("double %s\n", str + start);
	// 	return (NULL);
	// }
	free(buff);
	str_parssing = NULL;
	return (str_parssing);
}

/*
	verif is -n if true
	i = start str
	j = end str
*/
static char	*parssing_echo(char *str)
{
	char	*str_return;
	// char	*opt;
	int		i;
	int		j;

	// opt = recover_word(str, 2);
	i = 2;
	j = word_has_print_return_pos_finish(str, &i);
	i = recover_word_plus_return_position(str, --i);
	// printf("test >%s<\n", str + i);
	// printf("test fin >%s<\n", str + j);
	str_return = gest_symbole(str, i, j);
	// if (ft_strncmp(opt, "-n", 3) != 0)
	// 	str_return = ft_strjoin(str_return, "\n");
	// free(opt);
	return (str_return);
}

void	ft_echo(char *str)
{
	char	*print_str;

	// parssing_echo(str);
	// print_str = recover_word(str, 2);
	print_str = parssing_echo(str);
	printf("%s", print_str);
	// printf("%s", str);
	free(print_str);
}
