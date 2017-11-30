#ifndef EXCL_H
# define EXCL_H

#include "shell.h"

# define S_BEGIN 1
# define S_IN 2

typedef struct	s_entry
{
	char		*line;
	int			timestamp;
}				t_entry;

typedef struct	s_hist
{
	t_entry		*entry;
	int			offset;
	int			length;
	int			size;
}				t_hist;

t_hist			**global_hist(void);
int				sh_hist_add(char *new, int t);
int				sh_hist_del(char *str);
void			sh_hist_disp(int k);
t_hist			**sh_hist_read(void);
void			sh_hist_write(void);
char			*sh_hist_move(char move);
int				sh_history_opt(char **av, char *opt);
int				sh_history(char **av);


#endif
