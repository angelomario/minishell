/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:08:32 by joandre           #+#    #+#             */
/*   Updated: 2024/10/23 05:42:52 by joandre          ###   ########.fr       */
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

typedef struct s_master
{
	pid_t	*pid;
	char	*imput;
	char	**in;
	char	**history;
	char	**environ;
	char	***cmd;
	int		status;
	pid_t	pid_child;
}			t_master;

// char	**ft_split(char const *s, char c);
int			ft_builting(char **args);
void		ft_bin(char **av);
char		*ft_strstr(char *s1, char *s2);
void		free_matriz(char **mat);

// BUILT-INS
int			ft_cmd_built_ins(t_master *master, char **av);
int			ft_env(t_master *master);
int			ft_echo(char **av);
int			ft_unset(t_master *master, char **str);
void		ft_exit(t_master *master);
void		*ft_realloc(void *ptr, size_t new_size);
int			ft_export(t_master *master, char *name, char *value);
char		**ft_arrdup(char **environ);
int			ft_count_matriz(char **mat);
int			filter_export(t_master *master);
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
int			ft_heredoc(char *del);
#endif
