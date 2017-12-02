#include "shell.h"

static void	sh_hwrite(char *line, int fd)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1])
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(line[i++], fd);
	}
}

int			sh_hist_write(char *line, char *last)
{
	struct passwd	*pw;
	int				fd;
	int				i;

	if (!(pw = getpwuid(getuid())) || !line)
		return (1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && !ft_strequ(line, last))
	{
		if ((fd = open(sh_getvar("HISTFILE"), O_WRONLY | O_APPEND | O_CREAT,
						S_IRUSR | S_IWUSR)) < 0)
			return (1);
		sh_hwrite(line, fd);
		close(fd);
	}
	return (0);
}
