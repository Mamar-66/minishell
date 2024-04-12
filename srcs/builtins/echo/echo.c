/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:56:15 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/12 17:24:07 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


/* static char *buff_val(char *str, char sym, int *val_ptr)
{
	char	*str_return;
	char	*buff_tmp;
	int		i;

	i = *val_ptr;
	str_return = recover_word(str, i++, false);
	buff_tmp = recover_word(str, i++, false);
	while (ft_strchr(buff_tmp, sym) == NULL)
	{
		str_return = ft_strjoin(str_return, buff_tmp);
		free(buff_tmp);
		buff_tmp = recover_word(str, i++, false);
	}
	str_return = ft_strjoin(str_return, buff_tmp);
	free(buff_tmp);
	*val_ptr = --i;
	printf("text = %s\n", str_return);
	printf("nb = %d\n", i);
	return (str_return);
} */

/*
	gest symbole " end ' end $
*/
static void	gest_symbole(char *str, int start, t_data *lst_data)
{
	// char	*buff_str;
	// char	*str_return;
	char	*buff;
	// int		i;

	// i = 1;
	// str_return = ft_strdup("");
	buff = recover_word(str + start, 1, false);
	while (buff)
	{
		if (ft_strchr(buff, '\''))
			single_quote(str + start, '\'', &start);
		else if (ft_strchr(buff, '"'))
			double_quote(buff, lst_data);
		else
		{
			//printf("buff = %s\n", buff);
			simple_str(str + start, lst_data, &start);
			//printf("\nstr = %s\n", str + start);
		}
		printf(" ");
		// str_return = ft_strjoin(str_return, buff_str);
		// str_return = ft_strjoin(str_return, " ");
		// free(buff_str);
		// free(buff);
		// printf("\ntext = %s\n", str + start);
		buff = recover_word(str + start, 1, false);
	}
	// printf(">%s<", str_return);
	// free(buff);
}

/*
	verif is -n if true
	i = start str
	j = end str
*/

void	ft_echo(char *str, t_data *lst_data)
{
	char	*opt;
	int		i;

	i = 2;
	opt = recover_word(str, 2, false);
	if (!opt)
	{
		printf("\n");
		return;
	}
	if (word_has_print_return_pos_finish(str, &i) != -1)
	{
		i = recover_word_plus_return_position(str, --i);
		gest_symbole(str, i, lst_data);
	}
	if (ft_strncmp(opt, "-n", 3) != 0)
		printf("\n");
}
