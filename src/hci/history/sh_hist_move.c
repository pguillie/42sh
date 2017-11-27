#include "shell.h"

char		*sh_hist_line(char move)
{
	t_hist **hist;

	if (!(hist = global_hist()))
		return (NULL);
    if (move == '-' && (*hist)->offset > 0)
        (*hist)->offset--;
    else if (move == '+' && (*hist)->offset < (*hist)->length)
        (*hist)->offset++;
	return ((*hist)->entry[(*hist)->offset].line);
}

//actualiser l offset t_hist
