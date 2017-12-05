/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_usages.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 21:00:31 by mdescamp          #+#    #+#             */
/*   Updated: 2017/12/05 00:30:51 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_USAGES_H
# define SH_USAGES_H

# define SH_ILL_OPT(fct, opt) fct": illegal option -- "opt

# define SH_CD "usage: cd [-[L|P]] [directory]"
# define SH_DECLARE "usage: declare [-rx] [-p] [name[=value] ...]"
# define SH_ENV "usage: env [-i] [name=value] ... [utility [argument ...]]"
# define SH_EXPORT "usage: export [-p] name[=value] ..."
# define SH_HASH "usage: hash [-r] [utility...]"
# define SH_RDONLY "usage: readonly [-p] name[=value] ..."
# define SH_UNSET "usage: unset [-fv] name ..."

#endif
