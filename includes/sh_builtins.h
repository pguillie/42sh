#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

int		sh_ill_opt(char *fct, char opt, char *usage);

int		sh_cd(char **av);
int		sh_declare(char **av);
int		sh_echo(char **av);
int		sh_env(char **av);
int		sh_exit(char **av, int ret);
int		sh_export(char **av);
int		sh_hash(char **av);
int		sh_printenv(char *var);
int		sh_readonly(char **av);
int		sh_setenv(char **av);
int		sh_unset(char **av);
int		sh_unsetenv(char **av);

int		sh_cd2(char *dir, char *path, char opt);
int		sh_cd_access(char *path, char *dir);

#endif
