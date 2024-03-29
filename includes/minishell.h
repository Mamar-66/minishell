/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:20 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/29 15:08:53 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	int	status;
}	t_data;
/*
	add_signal/add_signal.c
*/
// static void	gest_signal(int numsignal);
// static void	gest_ctrl_D(t_data *lst_data);

char	*add_signal_plus_return_result_prompt(t_data *lst_data);

/*
			builtins
*/
void	ft_echo(char *str);
/*
			get_next_line
*/
char	*get_next_line(int fd);
/*
			get_pwd
*/
char	*return_pwd(void);
/*
			prompt
*/
char	*get_result_prompt(void);
// static bool	built_or_cmd(char str);
bool	gest_readline_recover(char *str);
/*
			utiles
*/
// static char	*first_word(char *str, int *start);
char	*recover_word(char	*str, unsigned int word_location);
int		recover_word_plus_return_position(char	*str,
			unsigned int word_location);
#endif