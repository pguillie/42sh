/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:24 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/02 22:40:00 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_PARSER_H
# define SH_PARSER_H

# include "shell.h"

void	sh_cmd_del(t_cmd **cmd);
t_cmd	*sh_cmd_new(t_token *lexer);
int		sh_list_del(t_cmd ****cmd_list, int **op);
int		sh_parser(t_token *lexer, t_cmd ****list, int **op);

#endif
