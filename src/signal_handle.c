/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:28:35 by pedro             #+#    #+#             */
/*   Updated: 2022/09/27 17:30:05 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Primeira funcao: default signals
    Correspondentemente a como o bash
    funciona, o Ctrl+\ (SIGQUIT)
    nao faz nada. Therefor, apenas return
    no fundo retirando o comando.

    O outro e para o caso de estar a
    haver input na shell. Ele vai ^C
    e introduzir uma nova linha*/

static void	def_signals(int sig)
{
	if (sig == SIGQUIT)
	{
		return ;
	}
	else if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

/* Segunda funcao: Heredoc Signals
	Correspondentemente a como o bash
	funciona, o Ctrl+\ (SIGQUIT)
	nao faz nada. Therefor, apenas return
	no fundo retirando o comando.

	O SIGINT e para dar display que o
	bash exibe e fecha o heredoc, no
	fundo intrerrompendo o funcionamento
	antes de estar concluido*/

static void	heredoc_sig(int sig)
{
	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
	{
		// signal(SIGINT, SIG_IGN);
		exit(0);
		// write(STDOUT_FILENO, "> ", 2);
		// write(STDOUT_FILENO, "\n", 1);
	}
}

// static void	sig_hub(int sig, int heredoc)
// {
// 	if (heredoc == 1)
// 		heredoc_sig(sig);
// 	else
// 		def_signals(sig);
// }

void	sigcall(void)
{
	signal(SIGINT, def_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	here_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sig);
}