/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:08:32 by joandre           #+#    #+#             */
/*   Updated: 2025/03/12 16:56:11 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <malloc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_master
{
	pid_t	pid;
	char	*imput;
	char	**in;
	char	*history;
	char	**environ;
	int		stdin_fd;
	int		stdout_fd;
	int		status;
	pid_t	pid_child;
	char	*output;
	char	**options;
	int		red;
}			t_master;

typedef struct s_wild
{
	char	*pos;
	char	*pre;
	char	*pattern;
	char	*path;
	char	*expr;
}			t_wild;

typedef struct s_data
{
	int		i;
	int		j;
	int		len;
	int		q_duo;
	int		q_s;
	char	*imput;
	int		var_start;
	char	*value;
	char	var_name[100];
	char	*oldpwd;
	char	*pwd;
	char	*dir;
	char	*error_msg;
}			t_data;

// char	**ft_split(char const *s, char c);
char		*ft_strstr(char *s1, char *s2);
void		free_matriz(char **mat);

// BUILT-INS
int			ft_env(t_master *master);
int			ft_echo(char **in);
int			ft_unset(t_master *master, char **str);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
int			ft_export(t_master *master, char *name, char *value);
int			export(t_master *master, char **in);
char		**ft_arrdup(char **environ);
int			ft_count_matriz(char **mat);
int			filter_export(t_master *master, char **in);
void		ft_arrtab(char **arr);
char		*remove_if_even(char *str, char ch);
void		ft_concert_env(t_master *master);
int			validpipe(char *str);
int			its_ok(char *str);
char		**ft_strsplit(char *s, char *delimiter);
void		rm_void(char **mat);
int			ft_pipe(t_master *master);
int			ft_cd(t_master *master, char **in);
int			ft_pwd(t_master *master, char **in);
void		sigint_handler(int sig);
// redirirection
int			ft_redirect(t_master *master, char *str);
char		*ft_check_type_redir(char *type_redir);
int			ft_len_redir(t_master *master, char **in);
int			redir_input(char *filename, int flag);
int			redir_output(char *name, int append);
char		**add_str(char **matrix, char *new_string);
int			to_configure(t_master *master, char *param, int flag,
				int (*f)(char *, int));
int			configure(t_master *master, char **in);
int			there_is_redirect(char **in);
int			do_heredoc(t_master *master, char **in);
char		**concatmatrix(t_master *master, char **mat1, char **mat2);
int			wait_sons(t_master *master);
// end redirection
char		**parsedel(char *imput);
void		format_imput(char **s, int n);
char		*expanded(t_master *master, char *imput);
int			ft_count_redir(char *s);
char		*ft_format_in_redir(char *s, int i, int j, char c);
void		trim_whitespace(char *str);
void		ft_bin(t_master *master, char **av);
char		*ft_getenv(char **env, char *name);
int			print_default_fd(t_master *master, char *msg);
int			is_redirect(char *str);
void		ft_setenv(t_master *master, char *name_var, char *new_value);
int			ft_count_redir(char *s);
int			is_redirect(char *str);
void		exit_130(int sig);
void		breaker(int sig);
void		str_replace_del(char *str, char target, char to_replace);
int			ft_clean_master(t_master *master);
char		*expan_env(t_master *master, char *imput);
int			ft_clean_master(t_master *master);
char		*ft_strncat(char *dest, char *source, size_t dest_size);
int			correct_pipes(char *str);
void		ft_replace_c(char *s);
void		ft_replace_c(char *s);
int			wait_sons(t_master *master);
int			ft_isalnum_more(int c);
void		str_replace_all(char *str, char target, char to_replace);
char		*get_name(char *str);
int			check_identifiers(t_master *master, char *str);
int			do_export(t_master *master, char *in);
int			filter_export(t_master *master, char **in);
char		*ft_very_and_bar(char *path);
int			ft_countchar(char *str, char ch);
int			currect_tmp(char *tmp);
int			wait_prompt(t_master *master);
int			do_pipe(t_master *master);
int			correct_pipes(char *str);
int			ft_find_way(t_master *master);
int			ft_valid_args(char **in);
int			replace_env(t_master *master, char *name, char *value);
char		*ft_joincheck(char *name, char *value);
int			check_permission(t_master *master, char *str);
int			ft_is_directory(t_master *master, char *str);
int			hered(t_master *master, char **mat);
int			check_commander(t_master *master, char *str);
int			is_built_in(t_master *master, char **in, char *tmp);
int			ft_exit(t_master *master, char **in, char *tmp);
int			ft_cleanredchild(t_master *master, char **command, char *tmp,
				char **in);
int			ft_masterclean(t_master *master);
int			ft_heredoc(t_master *master, char *del, char **mat, char **mat2);
int			ft_cleanpipechild(t_master *master, char **command, char *tmp,
				char **in);
int			quit_of_conf(t_master *master, char **in);
char		*proccess_wildcard(char *input);
char		*get_wildcard_expression(char *input, int wildpos);

// WILD CARDS
char		*get_rest(char *input);
char		*get_wildcard_expression(char *input, int wildpos);
char		*get_pathdir(char *input, int j);
char		*get_pos_wild(char *input, int j);
int			append_pattern(char **str, char *pattern);
int			construct_wild(char **expression, t_wild *wild);
char		*get_pre_wild(char *expr, int pos);
char		*get_pattern(char **pos, int i);
int			remove_word(char *str, int index);
char		**addstronmat(char ***mat, char *str);
int			set_waldcards(t_wild *wild, char **input);
int			clean_wild(t_wild *wild);
int			subst_word(char **str, char *to_add, int start);
int			concert_expr(char **expr);
void		do_wildcard(char **input);
int			compare_append(char **str, char *pattern);
int			update_expression(char **expression, char **mat);
int			in_quots(char *input, char ch);
#endif
