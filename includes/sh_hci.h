/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hci.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:19 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/07 16:17:15 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_HCI_H
# define SH_HCI_H

/*
**	HUMAN-COMPUTER INTERACTION
*/

int		sh_hci(t_tc *termcaps, t_token **lexer, int mret);

/*
**	COMPLETION
*/

char	**sh_tab_find(char *array[], char *dir, int cat);
int		sh_tab_init(char *str, size_t cur, char **lexeme, int *status);
int		sh_tab_ins(t_line *line, t_coord **coord, t_tc tc, char *buf);
int		sh_tab_multi(t_line *line, t_coord **coord, t_tc tc, char *array[]);
int		sh_tab(t_line *line, t_coord **coord, t_tc tc);
void	sh_tab_append(char **array[], char *occ, int c);
void	sh_tab_builtin(char **array[]);

/*
**	CONVERTIONS
*/

char	sh_conv_hex(char *str);
char	sh_conv_oct(char *str);
char	sh_conv(char *str);

/*
**	CUR_MOTION
*/

t_coord	*sh_create_coord(t_line *line, size_t prompt);
int		sh_move_able(char *esc, t_line *line, t_coord *coord, int *hist_search);
size_t	sh_move_cur(size_t origin, size_t dest, t_coord *coord, t_tc tc);
size_t	sh_move_line_u(t_line *line, t_coord *coord);
size_t	sh_move_line_d(t_line *line, t_coord *coord);
size_t	sh_move_word_r(t_line *line);
size_t	sh_move_word_l(t_line *line);

/*
**	EDITION
*/

int		sh_clear(t_line *line, t_coord **coord, t_tc tc);
int		sh_ctrl_d(t_line *line, char *save);
int		sh_cut_k(t_line *line, t_tc *tc);
int		sh_cut_u(t_line *line, t_coord **coord, t_tc *tc);
int		sh_cut_w(t_line *line, t_coord **coord, t_tc *tc);
int		sh_cvx(t_line *line, t_coord **coord, t_tc *tc, char byte);
int		sh_del_able(char *esc, t_line *line);
int		sh_del_l(t_line *line, t_coord **coord, t_tc tc);
int		sh_del_r(t_line *line);
void	sh_display_syntax(char *str);
int		sh_display(t_line *line, t_coord **coord, t_tc tc, char *save);
int		sh_edit_line(t_line **line, char *save, t_tc *tc);
int		sh_edit(t_line *line, char *last, t_token **lexer, t_tc *termcaps);
int		sh_esc(t_line **line, t_coord **coord, t_tc *tc, int *h_smd);
t_line	*sh_hist_able(char *esc, t_line *line, int *hist_search);
int		sh_hist(t_line **line, t_coord **coord, t_tc tc, t_line *target);
int		sh_ins(t_line *line, char c);
int		sh_nl(t_line *line, t_coord **coord, t_tc tc);
int		sh_paste(t_line *line, t_coord **coord, t_tc *tc);
int		sh_putesc(t_line **line, t_coord **coord, t_tc *tc, int *h_smd);
int		termput(int c);

/*
**	HISTORY
*/

t_line	**sh_ghist(void);
int		sh_hist_add(void);
void	sh_hist_del(void);
int		sh_hist_r(char *file);
t_line	*sh_hist_read(void);
int		sh_hist_write(char *line, char *last);
void	sh_hwrite(char *line, int fd, int eol);
t_line	*sh_hline_new(char *str, t_line *prev);
int		sh_i_search(t_line **line, t_tc *tc, int mode);
char	*sh_del_char(char *str);
char	*sh_ins_char(char *str, char c);
void	sh_i_prompt(char *str, t_tc *tc, int mode);
void	minedit_raz(t_line *line, t_tc *tc);
void	sh_print_file(t_line **file, t_line *line, t_tc *tc, int *j);

/*
**	LEXER
*/

int		sh_category(char *str, int i[2], int status[3]);
int		sh_lex_heredoc(char *str, int *i, char *fifo[32], t_token **list);
int		sh_lex_word(char **s, int t);
int		sh_lexer(t_token **list, char **str);
int		sh_metachar(char c);
int		sh_ctrl_op(char *str);
int		sh_rdir_op(char *str);
int		sh_token_del(t_token **begin);
int		sh_token_new(t_token **list, char *lexeme, int category);
int		sh_verification(t_token *lex, int ret);
int		sh_lex_eof(char *fifo[32], char *eof);

/*
**	PROMPT
*/

int		sh_print_prompt(char *ps);
int		sh_prompt_conv(char *ps, char buff[], int *b, int *len);
int		sh_prompt(int mode);
void	sh_prt_chr(char buff[], int *b, char c, int *len);
int		sh_prt_date(char buff[], int *b, char *ps, int *len);
int		sh_prt_esc(char buff[], int *b, char *ps);
int		sh_prt_host(char buff[], int *b, char h, int *len);
int		sh_prt_shell(char buff[], int *b);
int		sh_prt_strftime(char buff[], int *b, char *format, int *len);
int		sh_prt_term(char buff[], int *b, int *len);
int		sh_prt_time(char buff[], int *b, char t, int *len);
int		sh_prt_uid(char buff[], int *b);
int		sh_prt_user(char buff[], int *b);
int		sh_prt_vers(char buff[], int *b, char v);
int		sh_prt_wdir(char buff[], int *b, char w, int *len);

#endif
