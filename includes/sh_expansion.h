#ifndef SH_EXPANSION_H
# define SH_EXPANSION_H

t_token	*sh_expansion(t_token *lexer);
char	*sh_exp_tilde(char *lexeme);

int		sh_cmd_sub(t_token **exp);
char	*sh_only_b(char *str);
int		sh_squote(char *str);
int		sh_count_len(char *str);
int		sh_sub_sh(t_token *lex, char *tmp);

t_token	*sh_word_split(t_token **exp);
char	**ft_split_allwhite(char *str);

#endif
