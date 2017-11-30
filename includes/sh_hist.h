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
char		*sh_histexp_wcaret(t_token *w, char *str, int *i);
char		*sh_histexp_wdigit(t_token *w, char *str, int *i);
char		*sh_histexp_suff(char *exp, int i);
char		*sh_histexp_quote(char *exp, int i);
char		*sh_histexp_sub(char *exp, int i, char **sub);
char		*sh_histexp_new(t_token *w, int i, int j);
char		*sh_search(char *str, int l, t_hist *hist);
char		**sh_wmatch(void);
int			sh_list_len(t_token *list);

#endif
