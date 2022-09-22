/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 15:07:26 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 16:07:07 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	parser_utils(char *str, int *i)
{
	if (str[*i] == '\\')
	{
		(*i)++;
		if (!str[*i])
			syntax_error();
		(*i)++;
	}
	if (str[*i] && !is_diff_s(str, *i, "\"'"))
		*i = skip_quotes(str, *i);
}

/*
-Arguments:
[str] = the input recieved by [read_line]
[tree] = address of the binary tree

-Function:
	Takes and calls the main parsing functions to create
	the binary tree
*/
void	parser(char *str, t_tree **tree, int i, int count)
{
	t_pipe	*pipes;
	char	**matrix;

	pipes = NULL;
	str = treat_dollar2(str, (*envi()));
	check_pipes(str);
	while (str[i])
	{
		parser_utils(str, &i);
		if (str[i] && str[i] == '|' && str[i + 1] && str[i + 1] != '|')
		{
			tree_add_pipe(tree);
			add_pos(i, count, &pipes);
			count++;
		}
		while (str[i] && str[i] == '|')
			i++;
		if (str[i])
			i++;
	}
	matrix = separate_pipes(str, pipes);
	parse_all_pipes(str, matrix, tree);
	free_pipes(&pipes);
	free(str);
}

/*
-Arguments:
[matrix] = matrix with the string separated by pipes
[tree] = address of the binary tree

-Function:
	Sends one of the strings of the matrix to the function
	[parse_string] to be converted into tokens
*/
void	parse_all_pipes(char *str, char **matrix, t_tree **tree)
{
	t_parse	prs;

	prs.pos = 0;
	prs.ptr = tree;
	if (!matrix)
		parse_string(str, prs);
	else
	{
		while (matrix[prs.pos])
		{
			parse_string(matrix[prs.pos], prs);
			prs.pos++;
		}
	}
	free_matrix(matrix);
}

static int	parse_string_utils(char *str, t_parse prs, int *i2)
{
	int	i;

	i = *i2;
	if (str[i] && str[i] == '>' && str[i + 1] != '>')
		*i2 = add_case(str, i, OUT, prs);
	else if (str[i] && str[i] == '<' && str[i + 1]
		&& str[i + 1] != '<')
		*i2 = add_case(str, i, IN, prs);
	else if (str[i] && str[i] == '>' && str[i + 1]
		&& str[i + 1] == '>' && str[i + 2] != '>')
		*i2 = add_case(str, i, APD, prs);
	else if (str[i] && str[i] == '<' && str[i + 1]
		&& str[i + 1] == '<' && str[i + 2] != '<')
		*i2 = add_case(str, i, DOC, prs);
	else
		return (0);
	return (1);
}

/*
Arguments:
[str] = one of the strings that have been separated by pipes
[prs] = Struct with the address of the binary tree and the 
	position it is in the pipe matrix


-Function:
	Finds the position of a new token and send it to the funtion
	[add_case] to get the end of the token
*/
void	parse_string(char *str, t_parse prs)
{
	int	i;
	int	cmd;

	cmd = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (parse_string_utils(str, prs, &i))
			;
		else if (str[i] && str[i] == '-' && str[i + 1] && str[i + 1]
			&& is_diff_s(str, i + 1, "<>|&") && cmd)
			i = add_case(str, i - 1, FLG, prs);
		else if (str[i] && cmd != 0)
			i = add_case(str, i - 1, ARG, prs);
		else if (str[i])
		{
			i = add_case(str, i - 1, CMD, prs);
			cmd++;
		}
	}
}
