/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:20 by omfelk            #+#    #+#             */
/*   Updated: 2024/03/26 11:46:41 by omfelk           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_data
{
	int status;
} t_data;

/*
	add_signal/add_signal.c
*/
char	*add_signal_plus_return_result_prompt(t_data *lst_data);
/*
	get_pwd/get_pwd.c
*/
char	*return_pwd(void);
/*
	prompt/get_result_prompt
*/
char	*get_result_prompt(void);
#endif