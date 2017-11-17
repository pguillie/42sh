#ifndef SH_VAR_H
# define SH_VAR_H

char	***sh_var(void);
char	*sh_getvar(char *name);
int		sh_setvar(char *var, char *val);

#endif
