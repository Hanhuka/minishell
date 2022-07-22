/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:25:48 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/22 16:35:57 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_matrix(char **matrix)
{
	int	y;

	y = 0;
	printf("here\n");
	while (matrix[y])
	{
		printf("matrix[%d] = %s\n", y, matrix[y]);
		y++;
	}
}

int	is_dif(char c, char *chars)
{
	int i;

	i = 0;
	while (chars[i] != c)
		i++;
	if (!chars[i])
		return (1);
	return (0);
}

void	treat_quotes(char *str, int *i, int id, t_tree **ptr)
{
	int i2;

	i2 = *i;
	while (str[i2] && str[i2] != '"')
		i2++;
	if (!str[i])
		syntax_error(); //TO DO
	add_to_tree(id, strdup(str, (*i) + 1, i2 - 1)); // TO DO
}

void	add_to_tree(int id, char *str, t_tree **ptr)
{
	//TO DO
	// if (first string)
	// 	add_to((*ptr)->left)
	// else
	// 	add_to((*pre)->right)
}

int		add_case(char *str, int *i, int id, t_tree **ptr)
{
	if (!str[*i])
		syntax_error(); //TO DO
		i2 = *i;
	while (str[i2] && str[i2] == ' ')
		i2++;
	if (!str[i2] || !is_dif(str[i2], "<>|&"))
		syntax_error(); //TO DO
	while (str[i2] && is_dif(str[i2], "<>|& "))
		i2++;
	add_to_tree(id, strdup(str, (*i) + 1, i2 - 1), ptr); // TO DO
	*i = i2 + 1;
}

void	parse_string(char *str, t_tree **ptr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '>' && str[i + 1] != '>')
			add_case(str[i], &(i + 1), OUT, ptr);
		else if (str[i] == '<' && str[i + 1] != '<')
			add_case(str[i], &(i + 1), IN, ptr);
		else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
			add_case(str[i], &(i + 2), APD, ptr);
		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
			add_case(str[i], &(i + 2), DOC, ptr);
		else
			add_case(str[i], &(i + 2), CMD, ptr);
	}
}

void	tree_add_pipe(t_tree **tree)
{
	t_tree	*ptr;
	t_tree	*pipe;

	ptr = *tree;
	pipe = malloc(sizeof(*pipe));
	pipe->id = PIPE;
	pipe->left = NULL;
	pipe->right = NULL;
	pipe->up = NULL;
	if (!ptr)
	{
		*tree = pipe;
		return;
	}
	while (ptr->up)
		ptr = ptr->up;
	ptr->up = pipe;
	pipe->left = ptr;
}

char	*ft_substr(char *str, int start, int end)
{
	char	*sub;
	int		i;

	i = 0;
	if ((end - start) <= 0)
		return (NULL);
	sub = malloc(end - start + 1);
	while (start <= end)
	{
		sub[i] = str[start];
		start++;
		i++;
	}
	sub[i] = 0;
	return (sub);
}

char	**separate_pipes(char *str, t_pipe *pipes)
{
	int		i;
	char	**matrix;
	t_pipe	*ptr;

	i = 1;
	ptr = pipes;
	if (!pipes)
		return (NULL);
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	printf("size = %d\n", i);
	matrix = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (pipes)
	{
		printf("start = %d, end = %d\n", i, pipes->pos);
		matrix[pipes->count] = ft_substr(str, i, pipes->pos - 1);
		i = pipes->pos + 1;
		if (!pipes->next)
		{
			printf("LAST i = %d\n", i);
			matrix[pipes->count + 1] = ft_substr(str, i, ft_strlen(str) - 1);
			matrix[pipes->count + 2] = 0;
			// printf("LAST = %d\n", pipes->count);
		}
		printf("pipes->count = %d\n", pipes->count);
		pipes = pipes->next;
	}
	return (matrix);
}

// void	check_redir_in(t_pipe *pipes, char *str)
// {

// 	while (i < pipes->pos)
// 	{
// 		if (str[i] == '<' && (!str[i + 1] || str[i + 1] != '<'))
// 			i = input(str, i);
// 		else if (str[i] == '<' && str[i + 1] == '<' && (!str[i + 2] || str[i + 2] != '<'))
// 			i = heredoc(str, i);
// 		i++;
// 	}
// }

// void	is_command(int i, int i2)
// {
// }

// void	check_command(char *str)
// {
// 	int i;
// 	int i2;

// 	int i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != '>' && str[i] != '<' && str[i] != '|')
// 		{
// 			i2 = i;
// 			while (str[i] && str[i] != '>' && str[i] != '<')
// 				i++;
// 			while (str[i2] && str[i2] != '>' && str[i2] != '<')
// 				i2--;
// 			if ((!str[i] || str[i] != '<') && (!str[i2] || str[i2] != '>'))
// 				is_command(i, i2);
// 		}
// 		while (str[i] && str[i] == '<' && str[i] == '>')
// 			i++;
// 	}
// }

void	add_pos(int pos, int count, t_pipe **pipes)
{
	t_pipe *new;
	t_pipe *ptr;

	ptr = *pipes;
	new = malloc(sizeof(*new));
	new->pos = pos;
	new->next = NULL;
	new->count = count;
	if (!ptr)
	{
		*pipes = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	parser(char *str, t_tree **tree)
{
	int		i;
	int		count;
	t_pipe	*pipes;

	pipes = NULL;
	i = 0;
	count = 0;
	//create pipes in the binary tree
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|')
		{
			tree_add_pipe(tree);
			add_pos(i, count, &pipes);
			count++;
		}
		//funcao que guarda localizacao dos pipes
		while (str[i] == '|')
			i++;
		i++;
	}
	print_matrix(separate_pipes(str, pipes));
}

void	parse_all_pipes(char **matrix, t_tree **tree)
{
	int		y;
	t_tree	*ptr;

	ptr = *tree;
	y = 0;
	while (matrix[y])
	{
		parse_string(matrix[y], &ptr);
		// parse_pipe(matrix[y], y, &ptr);
		ptr = ptr->up;
		y++;
	}
}

parse_pipe(char *str, int y, t_tree **ptr)
{
}

int main()
{
	t_tree *tree;

	tree = NULL;
	parser("texto|texto|textotexto|texto|textotexto|texto|textotexto|texto||texto", &tree);

	
	// t_tree	*ptr;
	// ptr = tree;
	// while(ptr)
	// {
	// 	printf("%d\n", tree->id);
	// 	ptr = ptr->up;
	// }
	// while (1)
	// 	printf("readline = %s\n", readline("prompt -> "));
}
