#ifndef SH_STRUCT_H
# define SH_STRUCT_H

typedef struct	s_entry
{
	char		*line;
	int			timestamp;
}				t_entry;

typedef struct	s_hist
{
	t_entry		*entry;
	int			offset;
	int			length;
	int			size;
}				t_hist;

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct	s_tc
{
	t_coord	*coord;
	int		cut;
	int		prompt;
	char	*clipboard;
	char	*esc;
	char	data[2048];
	char	buff[2048];
	char	*cd;
	char	*ce;
	char	*dn;
	char	*le;
	char	*nd;
	char	*up;
	char	*vi;
	char	*ve;
}				t_tc;

typedef struct	s_line
{
	char			*str;
	char			*tmp;
	size_t			cur;
	size_t			pos;
	int				h_smd;
	size_t			h_pos;
	size_t			used;
	size_t			capacity;
}				t_line;

typedef struct	s_token
{
	char			*lexeme;
	int				category;
	struct s_token	*next;
}				t_token;

typedef struct	s_redir
{
	char	*type;
	int		left;
	char	*right;
	int		file;
}				t_redir;

typedef struct	s_cmd
{
	char			**av;
	size_t			nb_redir;
	struct s_redir	*redir;
}				t_cmd;

typedef struct	s_htable
{
	char			*cmd;
	char			*path;
	struct s_htable	*next;
}				t_htable;

#endif
