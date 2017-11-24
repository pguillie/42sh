/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:50:44 by pguillie          #+#    #+#             */
/*   Updated: 2017/11/24 15:31:46 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_wait(pid_t child, int ret)
{
	waitpid(child, &ret, WUNTRACED);
	waitpid(child, &ret, WUNTRACED);
	if (ret < 0)
		return (-1);
	if (WIFSTOPPED(ret))
	{
		kill(child, SIGKILL);
		wait(&ret);
	}
	if (WIFSIGNALED(ret))
	{
		write(1, "\n", 1);
		return (ret + 128);
	}
	return (WEXITSTATUS(ret));
}
