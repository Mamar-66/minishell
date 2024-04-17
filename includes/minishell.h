/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:20 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/17 20:30:24 by omfelk           ###   ########.fr       */
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
/*
	echo
*/
void	ft_echo(char *str, t_data *lst_data);
char	*simple_str(char *str, t_data *lst_data, int *val_ptr);
char	*quote(char *str, char sym, int *val_ptr, bool quote);
char	*double_quote(char *str, char sym, int *val_ptr);
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
bool	gest_readline_recover(char *str, t_data *lst_data);
/*
			utiles
*/
// static char	*first_word(char *str, int *start);
char	*recover_word(char	*str, unsigned int word_location, bool mod);
int		recover_word_plus_return_position(char	*str,
			unsigned int word_location);
int	word_has_print_return_pos_finish(char *str, int *pos_start);
#endif