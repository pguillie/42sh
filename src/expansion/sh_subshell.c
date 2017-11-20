#include "shell.h"

int		sh_sub_sh(t_token *lex, char *tmp)
{
	t_cmd		***cmd_blist;
	char		*tmplex;
	int			ret;
	int			*op;

	ret = LEX_OK;
	cmd_blist = NULL;
	op = NULL;
	tmplex = NULL;
	if (tmp && !lex)
	{
		tmplex = ft_strjoin(tmp, "\n");
		ret = sh_lexer(&lex, tmplex);
	}
	if (ret & LEX_OK)
	{
		sh_parser(sh_expansion(lex), &cmd_blist, &op);
		ret = sh_list_browse(cmd_blist, op, ret);
	}
	else
		ft_error("Syntax error", "unexpected end of file", NULL);
	tmplex ? free(tmplex) : 0;
	lex ? sh_token_del(&lex) : 0;
	cmd_blist ? sh_list_del(&cmd_blist, &op) : 0;
	return (ret & LEX_OK ? ret : -1);
}
