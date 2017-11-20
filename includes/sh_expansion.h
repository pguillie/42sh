#ifndef SH_EXPANSION_H
# define SH_EXPANSION_H

t_token	*sh_expansion(t_token *lexer);
char	*sh_exp_tilde(char *lexeme);

int		sh_cmd_sub(t_token **exp);
int		sh_sub_sh(t_token *lex, char *tmp);
int		sh_sub(t_token **exp);

t_token	*sh_word_split(t_token **exp);

#endif
