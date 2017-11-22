#include "shell.h"

int		sh_ill_opt(char *fct, char opt, char *usage)
{
	ft_putstr_fd(fct, 2);
	ft_putstr_fd(": illegal option -- ", 2);
	ft_putchar_fd(opt, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd(usage, 2);
	return (1);
}
