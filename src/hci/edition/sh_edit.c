/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:44:56 by pbourlet          #+#    #+#             */
/*   Updated: 2017/12/01 12:41:31 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	edit_raz(t_line *line, t_tc *tc, t_token **lexer)
{
	g_signal = 0;
	ft_bzero(line->str, line->used);
	line->used = 0;
	line->cur = 0;
	line->h_smd = 0;
	line->h_pos = 0;
	tc->esc = NULL;
	sh_token_del(lexer);
}

static int	edit_save(char **save, char *line)
{
	char	*tmp;

	tmp = *save;
	*save = ft_strjoin(*save, line);
	free(tmp);
	if (!*save)
		return (-1);
	return (0);
}

static int	edit_end(t_token **lexer, int ret, char *save)
{
	t_hist	**hist;

	if (!(hist = global_hist()))
		return (ft_error(E_SEVER, NULL, NULL));
	if (ret < 0 || ret & EOT || ret & SYN_ERR)
		sh_token_del(lexer);
	save ? ft_strdel(&save) : 0;
	return (g_signal == SIGINT ? 1 : ret);
}

int			sh_edit(t_line *line, t_token **lexer, t_tc *tc)
{
	struct termios	backup;
	char			*save;
	int				ret;

	if (term_raw(&backup, 0, 1))
		return (-1);
	ret = LEX_LOOP;
	save = NULL;
	while (ret & LEX_LOOP)
	{
		edit_raz(line, tc, lexer);
		tc->prompt = sh_prompt(!save ? 1 : 2);
		ret = sh_edit_line(&line, save, tc);
		ret = sh_hist_exp(line, ret);
		if (ret < 0 || ret == EOT || edit_save(&save, line->str) < 0
				|| (ret = sh_lexer(lexer, save)) < 0)
			break ;
		ret = sh_verification(*lexer, ret);
	}
	if (tcsetattr(0, TCSANOW, &backup) < 0 && (ret = -1))
		ft_error("Unable to restore termios structure", NULL, NULL);
	if (!(ret < 0 || ret & EOT) && !ft_strequ(line->str, "\n") &&
			!(line->str[ft_strlen(line->str) - 1] = '\0'))
		sh_hist_add(line->str, 0);
	return (edit_end(lexer, ret, save));
}
