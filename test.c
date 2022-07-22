#include "minishell.h"

int	is_alpha(char c)
{
	if (c > A && c < )
}

int	is_dup(char *str, int i)
{
	if (str[i - 1] && str[i] == str[i - 1]
	|| str[i + 1] && str[i] == str[i + 1])
		return (1);
	return (0);
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
	int	i2;
	int	i3;
	int	cmd;

	i = 0;
	while (str[i])
	{
		// if (str[i] == '"')
		// {
		// 	i2 = i + 1
		// 	while(str[i2] && str[i2] != '"')
		// 		i2++;
		// 	if (!str[i2])
		// 		unclosed_error(); // TO DO
		// 	i3 = i
		// 	while (str[i3] && str[i3] != '"')
		// 		i3--;
		// 	if (!str[i3])
		// 		add_to_tree(id = CMD, strdup(str, i + 1, i2 - 1)); // TO DO
		// 	i = i2 + 1;
		// }
		while (str[i] == ' ')
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
		// if (str[i] == '>' && str[i + 1] != '>')
		// {
		// 	if (!str[i + 1])
		// 		syntax_error(); //TO DO
		// 	i2 = i + 1;
		// 	while (str[i2] == ' ')
		// 		i2++;
		// 	if (str[i2] == '<' || str[i2] == '>' || str[i2] == '|' || str[i2] == '&')
		// 		syntax_error(); //TO DO
		// 	while (str[i2] && is_dif(str[i2], "><&| "))
		// 		i2++;
		// 	add_to_tree(id = CMD, strdup(str, i + 1, i2 - 1)); // TO DO
		// 	i = i2;
		// }
		// else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
		// {
		// 	if (!str[i + 2])
		// 		syntax_error(); //TO DO
		// 	i2 = i + 2;
		// 	while (str[i2] == ' ')
		// 		i2++;
		// 	if (str[i2] == '<' || str[i2] == '>' || str[i2] == '|' || str[i2] == '&')
		// 		syntax_error(); //TO DO
		// 	while (str[i2] && is_dif(str[i2], "><&| "))
		// 		i++;
		// 	add_to_tree(id = CMD, strdup(str, i + 1, i2 - 1)); // TO DO
		// }
	}
}