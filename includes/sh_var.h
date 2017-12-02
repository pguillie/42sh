/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_var.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:34 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 22:40:56 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_VAR_H
# define SH_VAR_H

char	*sh_getvar(char *name);
char	**sh_mkenv(void);
int		sh_setvar(char *name, char *value, char type);
int		sh_unsetvar(char *name, char type, char search);
char	***sh_var(void);
char	**sh_varsplit(char *value);

#endif
