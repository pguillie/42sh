/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_printvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:51:43 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/17 16:02:31 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//si type: afficher que type
//sinon: chercher dans options ET afficher options

static void	sh_printvar_out(char *fct, char *var, int type, int opt)
{
	int		i;

	ft_putstr(fct);
	ft_putchar(' ');
	if (var[0] & opt)
	{
		ft_putchar('-');
		(var[0] & V_EXPORT) && (opt & V_EXPORT) ? ft_putchar('x') : 0;
		(var[0] & V_RDONLY) && (opt & V_RDONLY) ? ft_putchar('r') : 0;
		ft_putchar(' ');
	}
	i = 1;
	while (var[i] && var[i] != '=')
		i++;
	write(1, var + 1, (var[i] ? i : i - 1));
	ft_putchar('\"');
	while (var[i])
	{
		(var[i] == '\"' || var[i] == '\\') ? ft_putchar('\\') : 0;
		ft_putchar(var[i++]);
	}
	ft_putstr("\"\n");
}

static int	sh_printvar_opt(char **av, int *opt)
{
	int		i;
	int		j;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		j = 1;
		if (av[i][j] == '-')
			break ;
		while (av[i][j])
		{
			if (av[i][j] == 'x')
				*opt |= V_EXPORT;
			if (av[i][j] == 'r')
				*opt |= V_RDONLY;
			j += 1;
		}
	}
}

static void	sh_printvar_type(char *fct, int type)
{
	char	***varray;
	int		i;

	if ((varray = sh_var()))
	{
		i = 0;
		while ((*varray)[i])
		{
			if ((*varray)[i][0] & type)
			{
				ft_putstr(av[0]);
				ft_putchar(' ');
				
			}
		}
	}
}

static void	sh_printvar_name(char *fct, char **av, 

int			sh_printvar(char **av, int type)
{
	char	***varray;
	int		opt;
	int		i;

	opt = 0;
	i = sh_printvar_opt(av, &opt);
	if (!av[i])
	{
		if (!(varray = sh_var()))
			return (-1);
		i = 0;
		while ((*varray)[i])
		{
			if ((*varray)[i][0] & opt)
				sh_printvar_var(av[0], (*varray)[i], );
		}
	}
	else
	{
		i = 0;
		while (av[i])
		{
			if (!sh_getvar(
		}
	}
}
