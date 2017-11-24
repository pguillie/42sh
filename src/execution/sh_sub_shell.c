#include "shell.h"

int		sh_small_main(char *cmd)
{
	t_token	*lexer;
	t_cmd	***cmd_list;
	int		*op;
	int		ret;

	ret = 0;
	lexer = NULL;
	cmd_list = NULL;
	op = NULL;
	if (sh_lexer(&lexer, cmd) < 0)
		ret = -1;
	else if (sh_parser(sh_expansion(lexer), &cmd_list, &op) < 0)
		ret = -1;
	else if (sh_list_browse(cmd_list, op, ret) < 0)
		ret = -1;
	lexer ? sh_token_del(&lexer) : 0;
	cmd_list ? sh_list_del(&cmd_list, &op) : 0;
	return (ret);
}

int		sh_sub_shell(char *cmd)
{
	pid_t	child;
	int		ret;

	ret = 0;
	if ((child = fork()) < 0)
		return (-1);
	if (child == 0)
	{
		cmd[ft_strlen(cmd) - 1] = '\n';
		ret = sh_small_main(cmd + 1);
		exit(ret);
	}
	else
		waitpid(child, &ret, WUNTRACED);
	return (WEXITSTATUS(ret));
}
