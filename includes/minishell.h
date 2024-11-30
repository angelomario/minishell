/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:08:32 by joandre           #+#    #+#             */
/*   Updated: 2024/11/29 08:42:11 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_L
# define MINISHELL_L

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

// int	*pid_address;

typedef struct s_master
{
	pid_t	pid;
	char	*imput;
	char	**in;
	char	*history;
	char	**environ;
	char	***cmd;
	int		stdin_fd;
	int		stdout_fd;
	int		status;
	pid_t	pid_child;
	char	*output;
}			t_master;

typedef struct s_data
{
	int		i;
	int		j;
	int		len;
	char	*imput;
	int		q_duo;
	int		q_s;
}			t_data;

int			g_func(int n);

// char	**ft_split(char const *s, char c);
int			ft_builting(char **args);
char		*ft_strstr(char *s1, char *s2);
void		free_matriz(char **mat);

// BUILT-INS
int			ft_cmd_built_ins(t_master *master);
int			ft_env(t_master *master);
int			ft_echo(char **in);
int			ft_unset(t_master *master, char **str);
void		ft_exit(t_master *master);
void		*ft_realloc(void *ptr, size_t new_size);
int			ft_export(t_master *master, char *name, char *value);
char		**ft_arrdup(char **environ);
int			ft_count_matriz(char **mat);
int			filter_export(t_master *master, char **in);
void		ft_arrtab(char **arr);
char		*ft_slice(char *str, char ch);
char		*remove_if_even(char *str, char ch);
void		ft_concert_env(t_master *master);
int			validpipe(char *str);
int			its_ok(char *str);
char		**ft_strsplit(char *s, char *delimiter);
int			heredoc(t_master *master, char **in);
void		rm_void(char **mat);
int			ft_pipe(t_master *master);
int			ft_cd(t_master *master, char **in);
int			ft_pwd(t_master *master, char **in);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);
int			ft_redirect(t_master *master, char *str);
char		**parsedel(char *imput);
int			ft_heredoc(t_master *master, char *del);
void		format_imput(char **s, int n);
char		*expanded(t_master *master, char *imput);
int			ft_count_redir(char *s);
char		*ft_format_in_redir(char *s, int i, int j, char c);
void		trim_whitespace(char *str);
int			is_built_in(t_master *master, char **in);
void		ft_bin(t_master *master, char **av);
char		*ft_getenv(char **env, char *name);
int			print_default_fd(t_master *master, char *msg);
int			is_redirect(char *str);
void		ft_setenv(t_master *master, char *name_var, char *new_value);
int			ft_count_redir(char *s);
int			is_redirect(char *str);
int			kill_proccess(int pid, char *del, int stdout);
int			is_heredoc(char **in);
void		exit_130(int sig);
void		breaker(int sig);
#endif
