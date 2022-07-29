/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_prints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:36:20 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/29 17:47:07 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_matrix(char **matrix)
{
	int	y;

	y = 0;
	if (!matrix)
	{
		// printf("NO MATRIX\n");
		return ;
	}
	while (matrix[y])
	{
		printf("matrix[%d] = %s\n", y, matrix[y]);
		y++;
	}
}

void	print_tokens(char *str, int id, int i, int i2)
{
	printf("___add_to_tree__________\nstart = %d\nend = %d\n", i, i2 - 1);
	if (id == CMD)
		printf("CMD\n");
	if (id == ARG)
		printf("ARG\n");
	if (id == FLG)
		printf("FLG\n");
	if (id == OUT)
		printf("OUT\n");
	if (id == IN)
		printf("IN\n");
	if (id == APD)
		printf("APD\n");
	if (id == DOC)
		printf("DOC\n");
	printf("Token = %s\n", ft_substr(str, i, i2 - 1));
	printf("________________________\n");
}

void	print_tree(t_tree *tree)
{
	t_tree	*ptr;
	int		count;

	count = 1;
	ptr = tree;
	if (!ptr)
		return ;
	printf("____________________________________\n");
	printf("PIPE %d LEFT\n", count);
	while (ptr)
	{
		if (ptr->id != PIPE)
			printf("STR = | %s |, ", ptr->str);
		if (ptr->id == CMD)
			printf("CMD\n");
		if (ptr->id == ARG)
			printf("ARG\n");
		if (ptr->id == FLG)
			printf("FLG\n");
		if (ptr->id == OUT)
			printf("OUT\n");
		if (ptr->id == IN)
			printf("IN\n");
		if (ptr->id == APD)
			printf("APD\n");
		if (ptr->id == DOC)
			printf("DOC\n");
		ptr = ptr->left;
	}
	// printf("____________________________________\n\n");
	printf("\n\n\n");
	while (tree)
	{
		ptr = tree;
		if (count == 1 && ptr->id != PIPE)
			return ;
		printf("____________________________________\n");
		printf("PIPE %d RIGHT\n", count);
		while (ptr)
		{
			if (ptr->id != PIPE)
				printf("STR = | %s |, ", ptr->str);
			if (ptr->id == CMD)
				printf("CMD\n");
			if (ptr->id == ARG)
				printf("ARG\n");
			if (ptr->id == FLG)
				printf("FLG\n");
			if (ptr->id == OUT)
				printf("OUT\n");
			if (ptr->id == IN)
				printf("IN\n");
			if (ptr->id == APD)
				printf("APD\n");
			if (ptr->id == DOC)
				printf("DOC\n");
			ptr = ptr->right;
		}
		// printf("____________________________________\n\n");
		printf("\n\n\n");
		tree = tree->up;
		count++;
	}
}
