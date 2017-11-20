#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

int		sh_cd(char *av[]);
int		sh_declare(char *av[]);
int		sh_echo(char *av[]);
int		sh_env(char *av[], char *env[]);
int		sh_exit(char *av[], int ret);
int		sh_export(char *av[]);
int		sh_hash(char *av[]);
int		sh_printenv(char *env[], char *var);
int		sh_readonly(char *av[]);
int		sh_setenv(char *av[]);
int		sh_setenv_var(char *prg, char *var);
int		sh_unset(char *av[]);
int		sh_unsetenv(char *av[]);

int		sh_access(char *dir, int mode);
int		sh_cd_exec(char opt, char *dir, int epu);
int		sh_cd2(char *dir, char opt, char *av);

#endif
