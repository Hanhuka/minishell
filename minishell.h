/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:15:43 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/29 16:59:29 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PIPE 1
#define CMD 2
#define IN 3
#define OUT 4
#define DOC 5
#define APD 6
#define ARG 7
#define FLG 8


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

//lib.c
int		ft_strlen(char *str);
char	*ft_substr(char const *str, int start, int end);
char	*ft_strdup(const char *s1);
int		is_dif(char c, char *chars);

//minishell.c
void	syntax_error(void);
void	add_to(int id, char *str, t_tree **tree, int side);
void	add_to_tree(int id, char *str, t_parse prs);
int		treat_dquotes(char *str, int i, int id, t_parse prs);
int		add_case(char *str, int i, int id, t_parse prs);
void	parse_string(char *str, t_parse prs);
void	tree_add_pipe(t_tree **tree);
char	**separate_pipes(char *str, t_pipe *pipes);
void	add_pos(int pos, int count, t_pipe **pipes);
void	parse_all_pipes(char *str, char **matrix, t_tree **tree);
void	parser(char *str, t_tree **tree);

//testing_prints.c
void	print_matrix(char **matrix);
void	print_tokens(char *str, int id, int i, int i2);
void	print_tree(t_tree *tree);

//erros_and_frees.c
void	free_matrix(char **matrix);
t_tree	**free_tree_utils(t_tree	**tree);
void	free_tree(t_tree **tree);

#endif