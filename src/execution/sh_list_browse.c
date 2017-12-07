/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_list_browse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 17:16:11 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/07 16:52:48 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_exec_cmd(t_cmd *cmd, int ret, int pipe)
{
	extern char	**environ;
	int			fd[10];
	int			std[3];
	int			i;

	i = 0;
	while (i < 10)
		fd[i++] = -1;
	sh_redir_backup(std);
	if (sh_redir_set(cmd->redir, fd))
	{
		sh_redir_restore(fd, std);
		return (1);
	}
	environ = sh_mkenv();
	if (cmd->av[0])
		ret = sh_execution(cmd->av, ret, pipe, cmd->sub);
	if (environ)
	{
		free(environ);
		environ = NULL;
	}
	if (sh_redir_restore(fd, std))
		return (-1);
	return (ret);
}

static int	sh_exec_pipe(t_cmd *cmd, int ret, int pipefd[2])
{
	int		stdout;

	close(pipefd[0]);
	stdout = dup(1);
	dup2(pipefd[1], 1);
	ret = sh_exec_cmd(cmd, ret, 1);
	dup2(stdout, 1);
	close(pipefd[1]);
	return (ret);
}

static int	sh_pipe(t_cmd **pipeline, int ret)
{
	pid_t	child;
	int		pipefd[2];
	int		stdin;
	int		test;

	if (!pipeline[1])
		return (sh_exec_cmd(pipeline[0], ret, 0));
	if (pipe(pipefd) < 0 || (child = fork()) < 0)
		return (-1);
	if (child == 0)
		exit(sh_exec_pipe(pipeline[0], ret, pipefd));
	else
	{
		close(pipefd[1]);
		stdin = dup(0);
		dup2(pipefd[0], 0);
		ret = sh_pipe(pipeline + 1, ret);
		dup2(stdin, 0);
		close(pipefd[0]);
	}
	kill(0, SIGTERM);
	waitpid(child, &test, 0);
	return (ret);
}

int			sh_list_browse(t_cmd ***list, int *op, int ret)
{
	t_cmd	**pipeline;
	int		i;
	int		j;
	int		o;

	i = 0;
	j = 0;
	if (list)
	{
		while ((pipeline = list[i]))
		{
			if (!i || (!(o = op[j++]) || ((o > 0 && !ret) || (o < 0 && ret))))
				ret = sh_pipe(pipeline, ret);
			i++;
		}
	}
	return (ret);
}
