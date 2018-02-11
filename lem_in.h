#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"

typedef struct	s_rooms
{
	char 			*name;
	short int		vstd;
	short int		blkd;
	struct s_rooms	*next;
}				t_rooms;

typedef struct	s_data
{
	int			n_ants;
	t_rooms		st;
	t_rooms		end;
	t_rooms		rooms;
	t_rooms		ways;
}				t_data;

#endif
