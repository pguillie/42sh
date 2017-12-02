#include "shell.h"

void	sh_hist_del(void)
{
	t_line	*tmp;
	t_line	**hist;

	if (!(hist = sh_ghist()))
		return ;
	while (*hist)
	{
		tmp = *hist;
		*hist = (*hist)->up;
		ft_strdel(&tmp->str);
		ft_memdel((void**)&tmp);
	}
}
