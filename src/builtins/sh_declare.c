/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_declare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:00:42 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/17 16:55:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_declare_usage(char opt)
{
  ft_putstr("declare: illegal option -- ");
  ft_putchar(opt);
  ft_putchar('\n');
  ft_putendl("usage: declare [-rx] [-p] [name[=value] ...]");
  return (1);
}

static int	sh_declare_opt(char **av, char *opt)
{
  int	i;
  int	j;

  i = 1;
  while (av[i] && av[i][0] == '-')
    {
      if (ft_strequ(av[i], "--") && ++i)
	break ;
      j = 1;
      while (av[i][j])
	{
	  if (av[i][j] == 'r')
	    opt[1] |= V_RDONLY;
	  else if (av[i][j] == 'x')
	    opt[1] |= V_EXPORT;
	  else if (av[i][j] == 'p')
	    opt[0] = 1;
	  else
	    return (-av[i][j]);
	  j++;
	}
      i++;
    }
  return (i);
}

static void	sh_declare_out(char *var)
{
  int	i;

  ft_putstr("declare ");
  if (var[0])
    {
      ft_putchar('-');
      var[0] & V_RDONLY ? ft_putchar('r') : 0;
      var[0] & V_EXPORT ? ft_putchar('x') : 0;
      ft_putchar(' ');
    }
  i = 1;
  while (var[i] && var[i] != '=')
    i++;
  write(1, var + 1, i - 1);
  if (var[i])
    {
      ft_putstr("=\"");
      while (var[i])
	{
	  if (var[i] == "\\" || var[i] == "\"")
	    ft_putchar("\\");
	  ft_putchar(var[i++]);
	}
      ft_putchar('\"');
    }
  ft_putchar('\n');
}

static int	sh_declare_print(char **av, int type)
{
  char	***varray;
  int	ret;
  int	i;
  int	l;

  if (!(varray = sh_var()))
    return (0);
  ret = 0;
  while (*av)
    {
      l = 0;
      while ((*av)[l] && (*av)[l] != '=')
	l++;
      i = 0;
      while ((*varray)[i])
	{
	  if (ft_strnequ((*varray)[i], *av, l) && (*varray)[i][l] == '=')
	    {
	      sh_declare_out((*varray)[i]);
	      break ;
	    }
	  i++;
	}
      if (!(*varray)[i] && (ret = 1))
	ft_error("declare", *av + 0, "not found");
    }
  if (i)
    return (ret);
  while ((*varray)[i])
    {
      if ((*varray)[i][0] & type)
	sh_declare_out((*varray)[i]);
      i++;
    }
  return (0);
}

int		sh_declare(char **av)
{
  char	opt[2]; //[0]=print [1]=type
  int	ret[2];
  int	i;

  ft_memset(opt, 0, sizeof(char) * 2);
  if ((i = sh_declare_opt(av, opt)) < 0)
    return (sh_declare_usage(-i));
  if (opt[0])
    return (sh_declare_print(av + i, opt[1]));
  ret[0] = 0;
  while (av[i])
    {
      if ((ret[1] = sh_setvar(av[i], NULL, opt[1])) < 0)
	return (-1);
      else if (ret[1] && (ret[0] = 1))
	ft_error(av[0], av[i], "not a valid identifier"); //peut mieux faire
      i++;
    }
  return (ret[0]);
}
