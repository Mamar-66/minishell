/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:20 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/14 11:12:41 by omfelk           ###   ########.fr       */
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

typedef struct s_lst_pipex
{
	char	**tab_path;
}	t_lst_pipex;


typedef struct s_data
{
	char		**env;
	char		**tenv;
	char		*t;
	char		**temp;
	int			status;
	int			fd_saved_std_out;
	int			fd_saved_std_in;
	bool		mod_lectur_for_read_final;
	t_lst_pipex lst_pipex;
}	t_data;
/*
	add_signal/add_signal.c
*/
// static void	gest_signal(int numsignal);
// static void	gest_ctrl_D(t_data *lst_data);

bool	ft_ex(char *str_traitement, t_data *lst_data, char **tab_free);
bool	ft_ex_father(char *str_traitement, t_data *lst_data);

char	*add_signal_plus_return_result_prompt(t_data *lst_data);

/*
	builtins
*/
/*
			ECHO
*/
void	ft_echo(char *str);
char	*simple_str(char *buff, char *str, int *start, t_data *lst_data);
char	*quote(char *str, t_data *lst_data);
char	*double_quote(char *str, t_data *lst_data);
/*
			PWD
*/
void	ft_pwd(void);
void	ft_env(char *str, t_data *en);
void	ft_export(char *argv, t_data *env);
int		good(char **trier);
char	**trie2(char **trier, char **temp, int i);
char	**ajoute(char **argv);
void	print(char **temp);
char	*ft_stjoin(char *temp, char *line);
int		v(char *str);
void	ft_cd(char *str, t_data *env);
void	fre(char **argv);
char	*ft_cdd(char **argv, t_data *env);
void	ft_unset(char *str, t_data *env);
void	ft_exportt(char *argv, t_data *env);
char	*verif(char *a);
char	*veriff(char *a, char *b, size_t i);
char	*ft_stoin(char *temp, char *line);
void	ft_exit(char *str, t_data *env);
void	ft_unsetbis(char *str, t_data *env);
int		findn(char *str);
int		ft_stcmp(const char *s1, const char *s2, size_t n);
void	metacarac(char *str, t_data *env);
void	changeenv(char **av, t_data *ev);
void	nodouble(char *str, t_data *env);
void	changes(char *pwd, char *oldpwd, t_data *env);
char	**decale(char **argv, int i);
int		notgood(char *str, t_data *env);
int		ftn(char *str);
void	extensiontwo(char **av, t_data *env, int i, int j);
void	extension(char **av, t_data *env, int i, int j);
char	*copy(char *str);
char	*encoress(char *temp, char **argv);
int	suiteverif(size_t i, char *a);
char *anothersuite(char *b);
int	nodif(char *str, char *s);
char	**trie(char **trier);
char	**plus(char **temp, t_data *env);
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
char	*redirect(char *buff, char *str, int *start, t_data *lst_data);
char	*verif_name_file(char *str, t_data *lst_data);

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
char	*ft_getenv(char	**tab_env, char *str_chrch);
void	freeverithing(t_data *env);
void	rempli(t_data *ev, char **en);
char	*recover_word(char	*str, unsigned int word_location, bool mod);
int		recover_word_plus_return_position(char	*str,
			unsigned int word_location);
int		word_has_print_return_pos_finish(char *str, int *pos_start);
char	*first_word(char *str, int *start, bool mod);
// my_fonction_free
void	my_free_tab(char **tab);

bool	ft_pipex(char *cmd, t_data *lst_data);

bool	built_or_cmd_for_father(char *str, t_data *lst_data, char **tab_arm_pipe);
#endif