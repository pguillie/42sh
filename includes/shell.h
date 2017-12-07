/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:36 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/07 12:00:41 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
**	EXTERN LIB
*/

# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>
# include <pwd.h>
# include <dirent.h>
# include <termcap.h>
# include <time.h>

/*
**	DEFINE
*/

# define SHELL "42sh"
# define VERSION "1.1.0"
# define HISTFILESIZE "500"
# define HISTSIZE "100"

# define HISTFILE "/.42sh_history"
# define PS1 "\\e[38;5;114m[\\@]\\e[0m \\e[38;5;74m\\w \\$\\e[0m "
# define PS2 "> "
# define PS3 "#? "
# define PS4 "+ "

# define PRT_SIZE 256
# define PATH_SIZE 2048
# define HASH_SIZE 10000

# define ERROR_MAX 5

# define EOT 8
# define EOL 4
# define LEXER 2
# define DISP 1
# define DISP_FULL 17

# define SYN_ERR 4
# define LEX_LOOP 2
# define LEX_OK 1

# define UP 1
# define DOWN 2
# define RIGHT 4
# define LEFT 8
# define END 32
# define HOME 128
# define CTL 64

# define HIST_SEARCH 4

# define CASE(x) (x | 32)

# define RDR_SPEC 1
# define RDR_AMBG -2
# define RDR_BADFD -3
# define RDR_NOENT -4
# define RDR_NORGHT -5
# define RDR_PIPE -6

# define V_EXPORT 1
# define V_RDONLY 2
# define V_FUNCT 4

/*
**	RESSOURCES
*/

# include "../libft/includes/libft.h"
# include "sh_category.h"
# include "sh_struct.h"
# include "sh_usages.h"

/*
**	PROTO
*/

# include "sh_builtins.h"
# include "sh_color.h"
# include "sh_execution.h"
# include "sh_expansion.h"
# include "sh_hash.h"
# include "sh_hci.h"
# include "sh_initialization.h"
# include "sh_parser.h"
# include "sh_signals.h"
# include "sh_var.h"

#endif
