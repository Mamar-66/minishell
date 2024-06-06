/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:36:20 by omfelk            #+#    #+#             */
/*   Updated: 2024/06/06 17:07:59 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

extern	int	g_global_numsignal;

typedef struct s_lst_pipex
{
	char	**tab_path;
}	t_lst_pipex;

typedef struct s_data
{
	int			i;
	int			pour_toi_simon;
	char		**env;
	char		**tenv;
	char		*t;
	char		**temp;
	int			status;
	int			fd_saved_std_out;
	int			fd_saved_std_in;
	int			fd_here_doc;
	int			numsignal;
	bool		here_doc;
	bool		here_doc_parssing;
	bool		mod_lectur_for_read_final;
	bool		is_pipe;
	t_lst_pipex	lst_pipex;
}	t_data;
/*
	add_signal/add_signal.c
*/
// static void	gest_signal(int numsignal);
// static void	gest_ctrl_D(t_data *lst_data);

bool	ft_ex(char **tab_ex, t_data *lst_data,
			char **tab_free, char **tab_free_dup);
bool	ft_ex_father(char *str_traitement, t_data *lst_data);
char	*add_signal_plus_return_result_prompt(t_data *lst_data);

/*
	builtins
*/
/*
			ECHO
*/
void	ft_echo(char *str, t_data *lst_data);
bool	verif_n(char *opt);
char	*simple_str(char *buff, char *str, int *start, t_data *lst_data);
char	*quote(char *str, t_data *lst_data);
char	*double_quote(char *str, t_data *lst_data);
/*
			PWD
*/
void	ft_pwd(t_data *lst_data);
void	ft_env(char *str, t_data *en);
void	ft_export(char *argv, t_data *env);
int		good(char **trier);
char	**trie2(char **trier, char **temp, int i);
char	**ajoute(char **argv);
void	print(char **temp, t_data *en);
char	*ft_stjoin(char *temp, char *line);
int		v(char *str);
void	ft_cd(char *str, t_data *env);
void	fre(char **argv);
char	*ft_cdd(char *str, char **argv, t_data *env);
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
int		suiteverif(size_t i, char *a);
char	*anothersuite(char *b);
int		nodif(char *str, char *s);
char	**trie(char **trier);
char	**plus(char **temp, t_data *env);
void	ft_error_and_status(t_data *en, char *str);
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
bool	here_doc_switch_stdin(t_data *lst_data, char *here_doc_end);
char	*redirect(char *buff, char *str, int *start, t_data *lst_data);
char	*redirect_right(char *str, int *start, t_data *lst_data);
char	*double_redirect_right(char *str, int *start, t_data *lst_data);
char	*redirect_left(char *str, int *start, t_data *lst_data);
char	*double_redirect_left(char *str, int *start, t_data *lst_data);
char	*verif_name_file(char *str, t_data *lst_data);

/*
			prompt
*/
char	*get_result_prompt(void);
// static bool	built_or_cmd(char str);
bool	gest_readline_recover(char *str, t_data *lst_data, char *reel);
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
void	ft_free_que_argv(char **argv);

bool	ft_pipex(char *cmd, t_data *lst_data);

bool	built_or_cmd_for_father(char *str, t_data *lst_data,
			char **tab_arm_pipe, char *str_reel);

char	*pour_toi_omar(char *str);
void	ft_change_numsignal(t_data *lst_data);
void	write_in_stdin(char *str, bool if_retourne_line,
			t_data *lst_data);
char	*inverse_split(char **tab);
char	*inverse_split_export(char **tab);

void	affiche_in_terminal(t_data *lst_data,
	char *readline_recover, char **tab_arm_pipe);
bool	av_ex(char *cmd);
char	**split_for_ex_pipe(char *str);

#endif