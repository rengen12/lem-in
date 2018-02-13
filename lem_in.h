#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"

# define FAIL	0
# define COMM	1
# define IGNORE	20
# define START	21
# define END	22
# define N_ANTS	3
# define ROOM	4
# define LINK	5

# define NVSTD	0
# define WTNG	1
# define VSTD	2
# define BLKD	3

typedef struct s_rooms	t_rooms;

typedef struct	s_neigh
{
	t_rooms			*room;
	struct s_neigh	*next;
}				t_neigh;

struct	s_rooms
{
	char 			*name;
	short int		stat;
	int				depth;
	struct s_rooms	*next; //for hash funct
	struct s_rooms	*prev; //for way building
	t_neigh			*neigh;
};

typedef struct	s_ways
{
	t_rooms			*head;
	int 			depth;
	struct s_ways	*other;
}				t_ways;

typedef struct	s_data
{
	int			n_ants;
	t_rooms		*st;
	t_rooms		*end;
	t_rooms		*ways;//?
	t_rooms		*rooms[100];
}				t_data;


int 	is_room(char *s);
#endif
