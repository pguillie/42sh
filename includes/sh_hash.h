/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:16 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 22:27:48 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_HASH_H
# define SH_HASH_H

void		sh_hash_disp(void);
int			sh_hash_fct(char *cmd);
void		sh_hash_free(void);
char		*sh_hash_get(char *cmd);
int			sh_hash_init(void);
t_htable	*sh_hash_new(char *cmd, char *path);
void		sh_hash_indapp(int new);
int			sh_hash_set(char *cmd, char *path);
int			*sh_hindex(void);
t_htable	**sh_htable(void);

#endif
