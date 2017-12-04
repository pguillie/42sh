/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:44:24 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/04 17:33:58 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_sub_cpy(int tube, char **cmd)
{
	char	b[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	ret = 1;
	tmp = NULL;
	while (ret > 0)
	{
		ft_bzero(b, BUFF_SIZE + 1);
		ret = read(tube, b, 1);
		if (b[0])
		{
			tmp = *cmd;
			*cmd = ft_strjoin(tmp, b[0] == '\"' ? "\\\"" : b);
			free(tmp);
		}
	}
	if (*cmd)
	{
		tmp = *cmd;
		if (tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = '\0';
	}
	return (0);
}

static int	sh_kill_zombie(pid_t child, int ret)
{
	if (WIFSIGNALED(ret) || (g_signal && g_signal != SIGWINCH))
	{
		kill(child, SIGKILL);
		wait(&ret);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

static char	*sh_sub_exec(char *tmp, int *ret)
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
		if (dup2(tube[1], 1) < 0)
			return (NULL);
		exit((*ret = sh_small_main(tmp)));
	}
	waitpid(exec, ret, WUNTRACED);
	close(tube[1]);
	if (!sh_kill_zombie(exec, *ret))
		sh_sub_cpy(tube[0], &cmd);
	else
		*ret = 2;
	return (cmd);
}

static void	sh_ret_exec(char **command, char *tmp, int *i)
{
	*command = sh_sub_exec(tmp, &(i[1]));
	if (i[2] == -2)
		i[2] = i[1];
	else if (i[2] != 0 || i[1] == 2)
		i[2] = i[1];
}

int			sh_cmd_sub(t_token **exp)
{
	char	**tmp;
	char	*command;
	char	*tmp2;
	int		i[5];

	ft_bzero(i, sizeof(int) * 5);
	i[2] = -2;
	if (!(tmp = sh_only_tab_b((*exp)->lexeme)))
		return (1);
	while (tmp[i[0]] && tmp[i[0]][0] != '`' && tmp[i[0]][0] && i[1] != 2)
	{
		sh_ret_exec(&command, tmp[i[0]], i);
		tmp2 = NULL;
		i[4] = ft_strlen(tmp[i[0]]);
		if (i[1] != 2)
			tmp2 = sh_cmd_ins((*exp)->lexeme, command, i);
		else
			g_signal = SIGINT;
		tmp2 ? free((*exp)->lexeme) : 0;
		tmp2 ? ((*exp)->lexeme = tmp2) : 0;
		command ? free(command) : 0;
		i[0]++;
	}
	ft_strtabdel(tmp);
	return (i[2]);
}
