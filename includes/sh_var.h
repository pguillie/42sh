#ifndef SH_VAR_H
# define SH_VAR_H

char	***sh_var(void);
char	*sh_getvar(char *name);
int		sh_setvar(char *name, char *value, char type);
int		sh_unsetvar(char *name, char type, char search);
char	**sh_mkenv(void);
char	**sh_varsplit(char *value);

#endif
