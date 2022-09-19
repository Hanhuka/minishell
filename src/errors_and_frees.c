/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_frees.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:45:28 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/19 10:20:11 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

t_tree	**free_tree_utils(t_tree	**tree)
{
	t_tree	*ptr;

	if (!(*tree))
		return (NULL);
	ptr = *tree;
	while (ptr->up)
		ptr = ptr->up;
	*tree = ptr;
	return (tree);
}

void	free_pipes(t_pipe **pipes)
{
	if (!pipes || !(*pipes))
		return ;
	free_pipes(&((*pipes)->next));
	free(*pipes);
	*pipes = NULL;
}

void	free_tree(t_tree **tree)
{
	if (!tree || !(*tree))
		return ;
	free_tree(&((*tree)->left));
	free_tree(&((*tree)->right));
	if ((*tree)->str)
		free((*tree)->str);
	free(*tree);
	*tree = NULL;
}

void	syntax_error(void)//TO DO
{
	write(1, "Syntax Error\n", 13);
	exit(1);
}
