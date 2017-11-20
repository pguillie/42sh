#ifndef SH_USAGES_H
# define SH_USAGES_H

#define SH_ILL_OPT(fct, opt) fct": illegal option -- "opt

# define SH_DECLARE "usage: declare [-rx] [-p] [name[=value] ...]"
# define SH_EXPORT "usage: export name[=value] ...\n        export -p"
# define SH_RDONLY "usage: readonly name[=value] ...\n        readonly -p"
# define SH_UNSET "usage: unset [-fv] name ..."

#endif
