#include "shell.h"

int		sh_init(t_tc *init)
{
	if (sh_init_var() < 0)
		return (-1);
	if (sh_init_termcaps(init))
		ft_error("Warning", "Line edition can't switch to advanced mode", NULL);
	sh_hash_init();
	sh_hist_read();
	return (0);
}
