#ifndef SH_USAGES_H
# define SH_USAGES_H

# define SH_ILL_OPT(fct, opt) fct": illegal option -- "opt

# define SH_DECLARE "usage: declare [-rx] [-p] [name[=value] ...]"
# define SH_ENV "usage: env [-i] [name=value] ... [utility [argument ...]]"
# define SH_EXPORT "usage: export [-p] name[=value] ..."
# define SH_RDONLY "usage: readonly [-p] name[=value] ..."
# define SH_UNSET "usage: unset [-fv] name ..."

#endif
