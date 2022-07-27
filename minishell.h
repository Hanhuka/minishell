/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:15:43 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/27 16:10:21 by ralves-g         ###   ########.fr       */
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
	int				nbr;
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
}	t_tree;

typedef struct s_parse
{
	t_tree	**ptr;
	int		pos;
}	t_parse;

typedef	struct s_string
{
	int		id;
	char*	str;
}	t_string;

#endif