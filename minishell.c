/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:25:48 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/27 17:48:02 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *str, int start, int end)
{
	char	*sub;
	int		i;

	i = 0;
	if (start > end)
		return (NULL);
	sub = malloc(end - start + 2);
	while (start <= end)
	{
		sub[i] = str[start];
		start++;
		i++;
	}
	sub[i] = 0;
	return (sub);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int		is_alphn(char c)
{
	if ((c >= 'A' && c <= 'Z') 
		|| (c >= 'a' && c <= 'z') 
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	print_matrix(char **matrix)
{
	int	y;

	y = 0;
	printf("here\n");
	if (!matrix)
	{
		printf("ERROR: NO MATRIX\n");
		exit(1);
	}
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

void	syntax_error(void)
{
	write(1, "Syntax Error\n", 13);
	exit(1);
}


void	add_to(int id, char *str,	t_tree **tree)
{
	t_tree	*branch;

	branch = malloc(sizeof(*branch));
	branch->id = id;
	branch->str = str;
	branch->left = NULL;
	branch->right = NULL;
	branch->up = *tree;
}

void	add_to_tree(int id, char *str, t_parse prs)
{
	t_tree *ptr;

	ptr = *(prs.ptr);

	while (ptr->right)
		ptr = ptr->right;
	if (prs.pos == 0)
		add_to(id, str, &ptr);
	else
		add_to(id, str, &ptr);
}

void	treat_dquotes(char *str, int i, int id, t_parse prs)
{
	int i2;

	i2 = i;
	while (str[i2] && str[i2] != '"')
		i2++;
	if (!str[i])
		syntax_error();
	add_to_tree(id, ft_substr(str, i + 1, i2 - 1), prs);
}

int		add_case(char *str, int i, int id, t_parse prs)
{
	int i2;

	if (id == DOC || id == APD || id == FLG)
		i += 2;
	else
		i++;
	if (str[i] == '"')
		treat_dquotes(str, i, id, prs);
	if (!str[i])
		syntax_error();
	i2 = i;
	while (str[i2] && str[i2] == ' ')
		i2++;
	if (!str[i2] || !is_dif(str[i2], "<>|&"))
		syntax_error();
	while (str[i2] && is_dif(str[i2], "<>|& "))
		i2++;
	add_to_tree(id, ft_substr(str, i, i2 - 1), prs); // TO DO
	return (i2 + 1);
}

void	parse_string(char *str, t_parse prs)
{
	int	i;
	int cmd;
	
	cmd = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '>' && str[i + 1] != '>')
			i += add_case(str, i, OUT, prs);
		else if (str[i] == '<' && str[i + 1] != '<')
			i += add_case(str, i, IN, prs);
		else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
			i += add_case(str, i, APD, prs);
		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
			i += add_case(str, i, DOC, prs);
		else if (str[i] == '-' && str[i + 1] && is_dif(str[i + 1], "<>|&"))
			i += add_case(str, i, FLG, prs);
		else if (cmd != 0)
			i += add_case(str, i, ARG, prs);
		else
			{
				i += add_case(str, i, CMD, prs);
				cmd++;
			}
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

char	**separate_pipes(char *str, t_pipe *pipes)
{
	int		i;
	char	**matrix;
	t_pipe	*ptr;

	i = 1;
	ptr = pipes;
	if (!pipes)
	{
		printf("ERROR: NO PIPES\n");
		return (NULL);
	}
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

void	parse_all_pipes(char **matrix, t_tree **tree)
{
	t_tree	*ptr;
	t_parse	prs;

	ptr = *tree;
	prs.pos = 0;
	while (matrix[prs.pos])
	{
		prs.ptr = &ptr;
		parse_string(matrix[prs.pos], prs);
		ptr = ptr->up;
		prs.pos++;
	}
}

void	parser(char *str, t_tree **tree)
{
	int		i;
	int		count;
	t_pipe	*pipes;
	char	**matrix;

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
	matrix = separate_pipes(str, pipes);
	print_matrix(matrix);
	parse_all_pipes(matrix, tree);
	// print_matrix(separate_pipes(str, pipes));
}


int main()
{
	t_tree *tree;

	tree = NULL;
	parser("texto>a|texto|textotexto|texto|textotexto|texto|textotexto|texto||texto", &tree);

	
	t_tree	*ptr;
	ptr = tree;
	while(ptr)
	{
		printf("%d\n", tree->id);
		ptr = ptr->up;
	// }
	// while (1)
	// 	printf("readline = %s\n", readline("prompt -> "));
}
