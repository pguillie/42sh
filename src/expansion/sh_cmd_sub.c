/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:44:24 by pbourlet          #+#    #+#             */
/*   Updated: 2017/11/21 12:03:29 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_sub_cpy(int tube, char **cmd)
{
	char	b[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	ret = 1;
	tmp = NULL;
	while (ret > 0)
	{
		ft_bzero(b, BUFF_SIZE + 1);
		ret = read(tube, b, BUFF_SIZE);
		if (b[0])
		{
			tmp = *cmd;
			*cmd = ft_strjoin(tmp, b);
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

char	*sh_sub_exec(char *tmp)
{
	int			tube[2];
	int			stat;
	pid_t		exec;
	char		*gnl;
	char		*cmd;

	pipe(tube);
	cmd = NULL;
	gnl = NULL;
	exec = fork();
	if (exec == 0)
	{
		close(tube[0]);
		dup2(tube[1], 1);
		sh_sub_sh(NULL, tmp);
		exit(0);
	}
	else
	{
		waitpid(exec, &stat, 0);
		close(tube[1]);
		sh_sub_cpy(tube[0], &cmd);
	}
	return (cmd);
}

char	*sh_sub_ins(char *lexeme, char *str)
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

int		sh_cmd_sub(t_token **exp)
{
	char	*command;
	char	*tmp;
	char	*str;

	str = (*exp)->lexeme;
	if (!(tmp = sh_only_b(str)))
		return (1);
	command = sh_sub_exec(tmp);
	free(tmp);
	tmp = sh_sub_ins((*exp)->lexeme, command);
	if (tmp)
	{
		free((*exp)->lexeme);
		(*exp)->lexeme = tmp;
	}
	command ? free(command) : 0;
	return (0);
}
