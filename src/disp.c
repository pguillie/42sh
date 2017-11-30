#include "shell.h"

// FONCTIONS DE DEBUGAGE //

void	displex(t_token *lex)
{
	ft_putendl("=== DISPLEX ===");
	while (lex)
	{
		ft_printf("category:%2d -- lexeme:%s\n", lex->category, lex->lexeme);
		lex = lex->next;
	}
	ft_putendl(" == end lex ==");
}

void	disphist(void)
{
	t_hist		**state;
	int			i;

	i = 0;
	state = global_hist();
	printf("\n===== HIST =====\n");
	printf("---STATE---\n");
	printf("offset: %d\n", (*state)->offset);
	printf("lengh: %d\n", (*state)->length);
	printf("size  : %d\n", (*state)->size);
	printf("---ENTRY---\n");
	while ((*state)->size + 1 != i )
	{
		printf("time: %10d --  ", (*state)->entry[i].timestamp);
		printf("line[%d]: %s\n", i, (*state)->entry[i].line);
		i++;
	}
	printf("===================\n");
}

void	dispcoord(t_coord *coord, t_line *line)
{
	size_t	i;

	i = 0;
	while (i <= line->used + 1)
	{
		ft_printf("%zu: (%d;%d) `%c'\n", i, coord[i].x, coord[i].y, line->str[i]);
		i++;
	}
}

void	disparser(t_cmd ***p, int *op)
{
	int i;
	int j;
	int	l;

	i = 0;
	ft_printf("$ $ $ DISPARSER $ $ $\n");
	if (p)
	{
		while (p[i])
		{
			j = 0;
			while (p[i][j])
			{
				l = 0;
				printf("NEW\n");
				while (p[i][j]->redir[l].type)
				{
					printf("\tREDIR: %d/%s/%s/%d\n",
							p[i][j]->redir[l].left,
							p[i][j]->redir[l].type,
							p[i][j]->redir[l].right,
							p[i][j]->redir[l].file);
					l++;
				}
				l = 0;
				while (p[i][j]->av[l])
				{
					printf("cmd: %s\n", p[i][j]->av[l]);
					l++;
				}
				j++;
			}
			p[i + 1] ? printf("--%d--\n", op[i]) : 0;
			i++;
		}
	}
	ft_printf("  $   ENDPARSER   $\n");
}

void	dispeof(char *fifo[32])
{
	int	i;

	i = 0;
	ft_putendl("### beg eof ###");
	while (i < 32 && fifo[i])
		ft_putendl(fifo[i++]);
	ft_putendl(" ## end eof ##");
}
