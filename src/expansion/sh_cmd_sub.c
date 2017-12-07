/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:44:24 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/07 16:52:35 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_sub_cpy(int tube, char **cmd)
{
	char	b[2];
	char	*tmp;
	int		ret;

	ret = 1;
	tmp = NULL;
	ft_bzero(b, 2);
	while (ret > 0)
	{
		if ((ret = read(tube, b, 1)))
		{
			tmp = *cmd;
			*cmd = ft_strjoin(tmp, b[0] == '\"' ? "\\\"" : b);
			free(tmp);
		}
	}
	if (((tmp = *cmd)) && (tmp[ft_strlen(tmp) - 1] == '\n'))
		tmp[ft_strlen(tmp) - 1] = '\0';
	return (0);
}

static int	sh_kill_zombie(int ret)
{
	if (ret || WIFSIGNALED(ret) || (g_signal && g_signal != SIGWINCH))
	{
		kill(0, SIGTERM);
		wait(&ret);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

static char	*sh_sub_exec(char *tab, int *ret)
{
	int			tube[2];
	pid_t		exec;
	char		*cmd;

	pipe(tube);
	cmd = NULL;
	if ((exec = fork()) < 0)
		return (NULL);
	if (exec == 0)
	{
		sh_dfl_sig();
		close(tube[0]);
		dup2(tube[1], 1);
		*ret = sh_small_main(tab);
		exit(*ret);
	}
	waitpid(exec, ret, WUNTRACED);
	close(tube[1]);
	if (!sh_kill_zombie(*ret) && *ret == 0)
		sh_sub_cpy(tube[0], &cmd);
	return (cmd);
}

static void	sh_ret_exec(char **command, char *tab)
{
	int		ret;

	ret = 0;
	*command = sh_sub_exec(tab, &ret);
}

int			sh_cmd_sub(t_token **exp)
{
	char	**tab;
	char	*command;
	int		j;
	int		l;

	j = 0;
	l = 0;
	tab = sh_cmd_tab_quote((*exp)->lexeme);
	command = NULL;
	while (tab && tab[j] && (!g_signal || g_signal == SIGWINCH))
	{
		if (tab[j][0])
			sh_ret_exec(&command, tab[j]);
		else
			command = NULL;
		l = sh_cmd_ins(*exp, command, l, ft_strlen(tab[j]));
		command ? free(command) : 0;
		j++;
	}
	ft_strtabdel(tab);
	return (0);
}
