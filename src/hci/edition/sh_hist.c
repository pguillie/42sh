#include "shell.h"

int		sh_hist(t_line **line, t_coord **coord, t_tc tc, char *target)
{
	free((*line)->str);
	(*line)->cur = sh_move_cur((*line)->cur, 0, *coord, tc);
	(*line)->str = ft_strdup(target);
	(*line)->used = ft_strlen(target);
	(*line)->pos = (*line)->used;
	return (LEXER | DISP);
}
