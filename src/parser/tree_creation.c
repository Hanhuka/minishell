/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:55:02 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 17:49:43 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
-Arguments:
[id] = What the token is (command, arg, input, output, etc...)
[str] = The actual content of the token
[tree] = The point of the tree where the new [branch] is getting
	added
[side] = If its the first command it goes the the left of the tree
	else goes to the right

			PIPE3
			/   \
		PIPE2   CMD4
		/   \
	PIPE1   CMD3
	/   \
 CMD1   CMD2
  
-Function:
	Adds the token (except pipes, they have already been added to 
		the tree) to the tree in its respective place
*/
void	add_to(int id, char *str, t_tree **tree, int side)
{
	t_tree	*branch;

	branch = malloc(sizeof(*branch));
	branch->id = id;
	branch->str = str;
	branch->left = NULL;
	branch->right = NULL;
	branch->up = *tree;
	if (!(*tree))
	{
		*tree = branch;
		branch->up = NULL;
	}
	else if (!side)
		(*tree)->left = branch;
	else
		(*tree)->right = branch;
}

void	add_to_tree_n(int id, char *str, t_tree **tree)
{
	t_tree	*ptr;

	if (!(*tree))
		add_to(id, str, tree, 0);
	else
	{
		ptr = *tree;
		while (ptr->left)
			ptr = ptr->left;
		add_to(id, str, &ptr, 0);
	}
}

/*
-Arguments:
[id] = What the token is (command, arg, input, output, etc...)
[str] = The actual content of the token
[prs] = Struct with the address of the binary tree and the 
	position it is in the pipe matrix

-Function:
	Adds the token (except pipes, they have already been added to 
		the tree) to the tree in its respective place
*/
void	add_to_tree(int id, char *str, t_parse prs)
{
	t_tree	*ptr;

	ptr = *(prs.ptr);
	while (prs.pos - 1 > 0)
	{
		ptr = ptr->up;
		prs.pos--;
	}
	if (prs.pos == 0)
		while (ptr->left)
			ptr = ptr->left;
	else
		while (ptr->right)
			ptr = ptr->right;
	if (prs.pos == 0)
		add_to(id, str, &ptr, 0);
	else
		add_to(id, str, &ptr, 1);
}

/*
-Arguments:
[str] = one of the strings that have been separated by pipes
[i] = the position the token starts
[id] = What the token is (command, arg, input, output, etc...)
[prs] = Struct with the address of the binary tree and the 
	position it is in the pipe matrix

-Function:
	Finds the end of the token that starts at position [i]
	and send it to the function [add_to_tree]
*/
int	add_case(char *str, int i, int id, t_parse prs)
{
	int	i2;

	if (id == DOC || id == APD)
		i++;
	i++;
	if (!str[i])
		syntax_error();
	i2 = i;
	while (str[i2] && (str[i2] == ' ' || str[i2] == '\t'))
		i2++;
	if (!str[i2] || !is_diff_s(str, i2, "<>|&"))
		syntax_error();
	while (str[i2] && is_diff_s(str, i2, "<>|& \t"))
	{
		if (!is_diff_s(str, i2, "\"'"))
			i2 = skip_quotes(str, i2);
		i2++;
	}
	if (*synt())
		return (0);
	if (!(*(prs.ptr)))
		add_to_tree_n(id, remove_quotes(ft_substr(str, i, i2 - 1)), prs.ptr);
	else
		add_to_tree(id, remove_quotes(ft_substr(str, i, i2 - 1)), prs);
	return (i2);
}
