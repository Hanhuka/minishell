/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:25:48 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/29 17:46:41 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(void)
{
	write(1, "Syntax Error\n", 13);
	exit(1);
}

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
	t_tree *ptr;

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
	t_tree *ptr;

	ptr = *(prs.ptr);
	while (prs.pos - 1 > 0)
	{
		ptr = ptr->up;
		prs.pos--;
	}
	// printf("CMD NBR = %d\n", prs.pos + 1);
	// printf("pipe nbr = %d\n", (*(prs.ptr))->pipenbr);
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
	// printf("ADD TO\n");
}

/*
-Arguments:
[str] = one of the strings that have been separated by pipes
[i] = the position the double quotes (") was found
[id] = What the token is (command, arg, input, output, etc...)
[prs] = Struct with the address of the binary tree and the 
	position it is in the pipe matrix

-Function:
	Takes the text in between quotes and groups it as one token
*/
int	treat_dquotes(char *str, int i, int id, t_parse prs)
{
	int i2;

	i2 = i + 1;
	while (str[i2] && str[i2] != '"')
		i2++;
	if (!str[i])
		syntax_error();
	//print_tokens(str, id, i, i2); // just for testing
	// add_to_tree(id, ft_substr(str, i, i2 - 1), prs);
	if (!(*(prs.ptr)))
		add_to_tree_n(id, ft_substr(str, i, i2 - 1), prs.ptr);
	else
		add_to_tree(id, ft_substr(str, i, i2 - 1), prs);
	return (i2 + 1);
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
int		add_case(char *str, int i, int id, t_parse prs)
{
	int i2;

	if (id == DOC || id == APD)
		i += 2;
	else
		i++;
	if (str[i] == '"')
		return (treat_dquotes(str, i + 1, id, prs));
	if (!str[i])
		syntax_error();
	i2 = i;
	while (str[i2] && str[i2] == ' ')
		i2++;
	if (!str[i2] || !is_dif(str[i2], "<>|&"))
		syntax_error();
	while (str[i2] && is_dif(str[i2], "<>|& "))
		i2++;
	// print_tokens(str, id, i, i2); // just for testing
	if (!(*(prs.ptr)))
		add_to_tree_n(id, ft_substr(str, i, i2 - 1), prs.ptr);
	else
		add_to_tree(id, ft_substr(str, i, i2 - 1), prs);
	if (id == ARG || id == CMD || id == FLG)
		return (i2);
	return (i2 + 1);
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
	int cmd;
	
	cmd = 0;
	i = 0;
	printf("______str = %s________\n\n\n", str);
	while (str[i])
	{
		// printf("str[i] = %c\n", str[i]);
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i] == '>' && str[i + 1] != '>')
			i = add_case(str, i, OUT, prs);
		else if (str[i] && str[i] == '<' && str[i + 1] != '<')
			i = add_case(str, i, IN, prs);
		else if (str[i] && str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
			i = add_case(str, i, APD, prs);
		else if (str[i] && str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
			i = add_case(str, i, DOC, prs);
		else if (str[i] && str[i] == '-' && str[i + 1] && is_dif(str[i + 1], "<>|&"))
			i = add_case(str, i, FLG, prs);
		else if (str[i] && cmd != 0)
			i = add_case(str, i - 1, ARG, prs);
		else if (str[i])
			{
				i = add_case(str, i - 1, CMD, prs);
				cmd++;
			}
	}
}

/*
-Arguments:
[tree] = address of the binary tree

-Funtion:
	Adds a new pipe module to the binary tree
*/

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
	pipe->str = NULL;
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


/*
-Arguments:
[str] = the input recieved by [read_line]
[pipes] = a linked list with every pipe, its position and its number

-Function:
	Separates the input by each pipe found into a matrix
*/
char	**separate_pipes(char *str, t_pipe *pipes)
{
	int		i;
	char	**matrix;
	t_pipe	*ptr;

	ptr = pipes;
	if (!pipes)
		return (NULL);
	while (ptr->next)
		ptr = ptr->next;
	matrix = malloc(sizeof(char *) * (ptr->count + 3));
	i = 0;
	while (pipes)
	{
		// printf("start = %d, end = %d\n", i, pipes->pos); // for testing
		matrix[pipes->count] = ft_substr(str, i, pipes->pos - 1);
		i = pipes->pos + 1;
		if (!pipes->next)
		{
			matrix[pipes->count + 1] = ft_substr(str, i, ft_strlen(str) - 1);
			matrix[pipes->count + 2] = 0;
		}
		pipes = pipes->next;
	}
	return (matrix);
}

/*
-Arguments:
[pos] = the position the pipe was found int the input
[count] = the number of the pipe
[pipes] = the linked list the pipe is going to get added

-Function:
	Adds a new pipe to the pipe linked list with its respective 
	position and count
*/
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

	printf("str = %s\n", str);
	prs.pos = 0;
	prs.ptr = tree;
	if (!matrix)
		parse_string(str, prs);
	else 
	{
		while (matrix[prs.pos])
		{
			// printf("matrix[%d] = %s\n",prs.pos, matrix[prs.pos]);
			parse_string(matrix[prs.pos], prs);
			prs.pos++;
		}
	}
}

int	parser_handle_dquotes(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '"')
		i++;
	if (!str[i])
		syntax_error();
	return (i);
}

/*
-Arguments:
[str] = the input recieved by [read_line]
[tree] = address of the binary tree

-Function:
	Takes and calls the main parsing functions to create
	the binary tree
*/
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
		if (str[i] && str[i] == '"')
			i = parser_handle_dquotes(str, i);
		if (str[i] && str[i] == '|' && str[i + 1] && str[i + 1] != '|')
		{
			tree_add_pipe(tree);
			add_pos(i, count, &pipes);
			count++;
		}
		while (str[i] && str[i] == '|')
			i++;
		i++;
	}
	matrix = separate_pipes(str, pipes);
	print_matrix(matrix);
	parse_all_pipes(str, matrix, tree);
	free_matrix(matrix);
}

//Need to free the pipe matrix, the pipe linked list, 
int main()
{
	t_tree	*tree;
	char	*line;

	tree = NULL;

	while (1)
	{
		line = readline("shell> ");
		if (!line)
		{
			printf("\nexit\n");
			exit(0);
		}
		if (!ft_strlen(line))
		{
			free(line);
			continue;
		}
		parser(line, &tree);
		add_history(line);
		print_tree(tree);
		free_tree(free_tree_utils(&tree));
	}
}
