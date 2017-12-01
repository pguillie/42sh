/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 15:14:22 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/01 17:20:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_HIST_H
# define SH_HIST_H

t_hist		**global_hist(void);
int			sh_hist_add(char *new, int t);
int			sh_hist_del(char *str);
void		sh_hist_disp(int k);
t_hist		**sh_hist_read(void);
void		sh_hist_write(void);
char		*sh_hist_move(char move);
int			sh_history_opt(char **av, char *opt);
int			sh_history(char **av);

char		*sh_histexp_line(int offset);
int			sh_hist_exp(t_line *line, int ret);
int			sh_histexp_id(char *str, int i);
int			sh_histexp_event(char *str, int i, char **exp, t_hist *hist);
int			sh_histexp_word(char *str, int i, char **exp);
int			sh_histexp_modif(char *str, int i, char **exp, int *b);
char		*sh_histexp_wcaret(t_token *w, char *str, int *i);
char		*sh_histexp_wdigit(t_token *w, char *str, int *i);
char		*sh_histexp_quote(char *exp, char c);
char		*sh_histexp_sub(char *exp, char *str, int *i, int global);
char		*sh_histexp_new(t_token *w, int i, int j);
char		*sh_search(char *str, int l, t_hist *hist);
char		**sh_wmatch(void);
char		**sh_hist_sub(void);
int			sh_list_len(t_token *list);

int			sh_i_search(t_line **line, t_tc *tc, int mode);
char		*sh_del_char(char *str);
char		*sh_ins_char(char *str, char c);
void		sh_i_prompt(char *str, t_tc *tc, int mode);
int			sh_cpy_hist(t_hist *hist, int *goffset, t_line **line);
int			sh_i_strstr(char *line, char *str, int mode);

#endif
