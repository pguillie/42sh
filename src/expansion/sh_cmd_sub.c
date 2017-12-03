/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:44:24 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/03 15:09:42 by lcordier         ###   ########.fr       */
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
			return (-1);
		exit((*ret = sh_small_main(tmp)));
	}
	waitpid(exec, ret, WUNTRACED);
	close(tube[1]);
	if (!sh_kill_zombie(exec, *ret))
		sh_sub_cpy(tube[0], &cmd);
	return (cmd);
}

static char	*sh_sub_ins(char *lexeme, char *str)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 0;
	while (lexeme[i] && lexeme[i] != '`')
		i++;
	tmp = ft_strndup(lexeme, i);
	res = ft_strjoin(tmp, str);
	tmp ? free(tmp) : 0;
	if ((!tmp && i) || !res)
	{
		free(res);
		return (NULL);
	}
	i = ft_strlen(lexeme) - 1;
	while (lexeme[i] && lexeme[i] != '`')
		i--;
	if (!lexeme[i])
		return (res);
	i++;
	tmp = res;
	res = ft_strjoin(tmp, lexeme + i);
	free(tmp);
	return (res);
}

int			sh_cmd_sub(t_token **exp)
{
	char	*command;
	char	*tmp;
	char	*str;
	int		ret;

	str = (*exp)->lexeme;
	if (!(tmp = sh_only_b(str)) || tmp[0] == '`')
	{
		tmp ? free(tmp) : 0;
		return (0);
	}
	command = sh_sub_exec(tmp, &ret);
	free(tmp);
	tmp = sh_sub_ins((*exp)->lexeme, command);
	if (tmp)
	{
		free((*exp)->lexeme);
		(*exp)->lexeme = tmp;
	}
	command ? free(command) : 0;
	return (!tmp ? -1 : ret);
}
