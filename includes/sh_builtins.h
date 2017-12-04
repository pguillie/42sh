/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 10:49:38 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/04 14:46:59 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

int		sh_cd_access(char *path, char *dir);
int		sh_cd(char **av);
int		sh_cd2(char *dir, char *path, char opt);

int		sh_declare(char **av);
int		sh_echo(char **av);
int		sh_env(char **av);
int		sh_exit(char **av, int ret);
int		sh_export(char **av);
int		sh_hash(char **av);

int		sh_history_opt(char **av, char *opt);
int		sh_history(char **av);

int		sh_ill_opt(char *fct, char opt, char *usage);

int		sh_printenv(char *var);
int		sh_readonly(char **av);
int		sh_setenv(char **av);
int		sh_unset(char **av);
int		sh_unsetenv(char **av);

#endif
