#include "shell.h"

int		sh_hist_size(void)
{
	int 	size;
	t_hist	**hist;

	size = 0;
	if (!(hist = global_hist()))
		return (-1);
	while ((*hist)->entry[size].line)
		size++;
	return (size);
}
