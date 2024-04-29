/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:20 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/29 16:31:24 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
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
	int	fd_saved_std_out;
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
void	ft_echo(char *str);
char	*simple_str(char *buff, char *str, int *start, t_data *lst_data);
char	*quote(char *str, t_data *lst_data);
char	*double_quote(char *str, t_data *lst_data);

void	ft_pwd(char *str);
/*
			get_next_line
*/
char	*get_next_line(int fd);
/*
			get_pwd
*/
char	*return_str_pwd(void);
char	*return_pwd(void);
/*
			parsing
*/
char	*parsing(char *str, t_data *lst_data);
// redirect
void	redirect(char *buff, char *str, int *start, t_data *lst_data);

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
int		word_has_print_return_pos_finish(char *str, int *pos_start);
char	*first_word(char *str, int *start, bool mod);
#endif