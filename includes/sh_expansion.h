/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansion.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:00:25 by pguillie          #+#    #+#             */
/*   Updated: 2017/12/02 14:06:02 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_EXPANSION_H
# define SH_EXPANSION_H

t_token	*sh_expansion(t_token *lexer);
char	*sh_exp_tilde(char *lexeme);

int		sh_cmd_sub(t_token **exp);
char	*sh_only_b(char *str);

t_token	*sh_word_split(t_token **exp);
char	**ft_split_allwhite(char *str);

int		sh_hist_exp(t_line *line, int ret);
int		sh_histexp_id(char *str, int i);
int		sh_histexp_event(char *s, int i, char **exp, t_line *hist);
int		sh_histexp_word(char *str, int i, char **exp);
int		sh_histexp_modif(char *str, int i, char **exp, int *b);
int		sh_list_len(t_token *list);
char	*sh_histexp_wcaret(t_token *w, char *str, int *i);
char	*sh_histexp_wdigit(t_token *w, char *str, int *i);
char	*sh_histexp_quote(char *exp, char c);
char	*sh_histexp_sub(char *exp, char *str, int *i, int global);
char	*sh_histexp_line(t_line *hist, int offset);
char	*sh_histexp_new(t_token *w, int i, int j);
char	*sh_histexp_search(char *str, int l, t_line *hist);
char	**sh_wmatch(void);
char	**sh_hist_sub(void);

#endif
