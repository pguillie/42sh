#include "shell.h"

static int		sh_convert_hist(char *esc)
{
	if (esc[1] == '[' && (esc[2] == 'A' || esc[2] == 'B'))
		return ((esc[2] ^ 64) | 4);
	else if (esc[1] == '[' && (esc[2] == '5' || esc[2] == '6') && esc[3] == '~')
		return (esc[2] ^ 52);
	return (0);
}

static int		sh_hist_search(t_line *line, int id)
{
	if (id & HIST_SEARCH)
	{
		if (!line->h_smd)
		{
			line->h_smd = 1;
			line->h_pos = line->cur;
		}
		return (1);
	}
	else
		return (0);
}

static char	*sh_get_target(t_line *line, char *target, int id)
{
	if (id & UP)
	{
		if (line->h_smd)
			// while (sh_hist_line('-') && (!ft_strnequ(line->str, sh_hist_line('-'),
			// 				line->h_pos) || !ft_strcmp(line->str, sh_hist_line('-'))))
				target = sh_hist_line('-');
	}
	else if (id & DOWN)
	{
		if (line->h_smd)
		// while (sh_hist_line('+') && (!ft_strnequ(line->str, sh_hist_line('+'),
		// 				line->h_pos) || !ft_strcmp(line->str, sh_hist_line('+'))))
				target = sh_hist_line('+');
	}
	if (!target)
		return (line->str);
	return (target);
}

char			*sh_hist_able(char *esc, t_line *line, int *hist_search)
{
	char	*target;
	int		id;

	target = NULL;
	id = sh_convert_hist(esc);
	*hist_search = sh_hist_search(line, id);
	target = sh_get_target(line, target, id);
	// printf("%s\n", target);
	return (target);
}
