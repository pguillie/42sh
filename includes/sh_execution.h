/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:12 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/03 12:01:33 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXECUTION_H
# define SH_EXECUTION_H

int		sh_exec_bin(char *cmd, char **path);
int		sh_cmd_exec(char **av, char *env[], char **path, int pipe);
int		sh_execution(char **av, int ret, int pipe, int sub);
int		sh_list_browse(t_cmd ***list, int *op, int ret);
int		sh_redir_backup(int std[3]);
int		sh_redir_restore(int fd[10], int std[3]);
int		sh_redir_set(t_redir *redir, int fd[10]);
int		sh_small_main(char *cmd);
int		sh_sub_shell(char *cmd);
int		sh_wait(pid_t child, int ret);

#endif
