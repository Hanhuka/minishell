/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:15:43 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/27 17:25:32 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#define PIPE 1
#define CMD 2
#define IN 3
#define OUT 4
#define DOC 5
#define APD 6
#define ARG 7
#define FLG 8

extern int g_status;

typedef struct s_exec
{
	int		p[2];
	pid_t	pid;
	int		count;
	int		in;
	int		out;
	int		pos;
	int		doc;
	char	***env;
}	t_exec;

typedef struct s_pipe
{
	int				pos;
	int				count;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_tree
{
	struct s_tree	*right;
	struct s_tree	*left;
	struct s_tree	*up;
	char*			str;
	int				pipe[2];
	int				id;
	int				pipenbr;
}	t_tree;

typedef struct s_parse
{
	t_tree	**ptr;
	int		pos;
}	t_parse;

typedef struct s_addvar
{
	char	*str;
	char	*var;
	char	**newstr;
	int		start;
	int		end;
	int		i;
	int		i2;
} t_add_var;

//lib.c
int			ft_strlen(const char *str);
char		*ft_substr(char const *str, int start, int end);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//lib2.c
int			ft_putstr_fd(char *str, int fd);
long int	ft_atoi(const char *str);
char		*ft_itoa(int n);

//split_join.c
char		**ft_split(char const *str, char c);
char		*ft_strjoin(char const *s1, char const *s2);

//minishell.c

//parse_pipes.c
void		tree_add_pipe(t_tree **tree);
char		**separate_pipes(char *str, t_pipe *pipes);
void		add_pos(int pos, int count, t_pipe **pipes);

//parser.c
void		parser_utils(char *str, int *i);
void		parser(char *str, t_tree **tree, int count, char **env);
void		parse_all_pipes(char *str, char **matrix, t_tree **tree);
void		parse_string(char *str, t_parse prs);

//parser_utils.c
void		check_pipes(char *str);
void		parser_utils2(char *str, int *i);
void		parser_utils3(char *str, t_tree **tree, int count, t_pipe **pipes);

//tree_creation.c
void		add_to(int id, char *str, t_tree **tree, int side);
void		add_to_tree_n(int id, char *str, t_tree **tree);
void		add_to_tree(int id, char *str, t_parse prs);
int			add_case(char *str, int i, int id, t_parse prs);

//env.c
char		**get_env(char **env);

//treat_dollar.c
int			is_var(char c);
int			till_eq(char *str);
char		*search_var(char *var, char **env);
void		add_var_util(t_add_var v);
char		*add_var(char *str, char *var, int start, int end);

//treat_dollar2.c
char		*get_var(char *str, int *i, char **env);
char		**treat_dollar(char **matrix, char **env);
char		*treat_dollar2(char *str, char **env);

//treat_dollar3.c
void	get_status_utils(char *str, int i, char *val, char **newstr);

//quotes.c
int			is_diff_s(char *str, int i, char *test);
int			skip_quotes(char *str, int i);
int			count_quotes(char *str);
char		*remove_quotes(char *str);

//backslash.c
int			nbr_backslash(char *str);
char		*rm_backslash(char *str, int i, int i2, char qt);

//testing_prints.c
void		print_matrix(char **matrix);
void		print_tokens(char *str, int id, int i, int i2);
void		print_tree(t_tree *tree);

//erros_and_frees.c
void		free_matrix(char **matrix);
t_tree		**free_tree_utils(t_tree **tree);
void		free_tree(t_tree **tree);
void		syntax_error(void);
void		free_pipes(t_pipe **pipes);

//erros_and_frees2.clong int	ft_atoi(const char *str)
int 	*synt(void);

//executor.c
void		executor(t_tree *tree, t_exec *e, int *fd);
t_exec		execute_command(t_tree	*tree, int pos, int count, char ***env);
void		execute_tree(t_tree **tree, char ***env);

//executor_prep.c
int			cmd_count(t_tree *tree);
char		*find_command(t_tree	*tree, int pos);
char		**get_path(char **env);


//executor_prep2.c
char		*not_absolute(char *cmd, char **path);
char		*absolute(char *cmd);
char		*cmd_path(char *cmd, char **env);
int			nbr_args(t_tree	*tree, int pos);
char		**get_args(t_tree *tree, int pos);

//redirections.c
int			count_redirect(t_tree *tree, t_exec *e, int id);
void		in_error(char *str);
void		open_in(t_tree *tree, t_exec *e);
void		open_out(t_tree *tree, t_exec *e);
void		redirections(t_tree *tree, t_exec *e, int *fd);

//heredoc.c
void		no_heredoc_utils(t_tree *tree, t_exec *e, int i);
void		heredoc_filler(int fd, char *eof);
void		ft_heredoc(t_tree *tree, t_exec *e, int i);

//signal_handle.c
void		sigcall(void);
void		here_sig(void);

#endif
