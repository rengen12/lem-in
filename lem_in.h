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

typedef struct	s_rooms	t_rooms;

typedef struct	s_neigh
{
	t_rooms			*room;
	struct s_neigh	*next;
}				t_neigh;

struct			s_rooms
{
	char 			*name;
	short int		stat;
	int				depth;
	struct s_rooms	*next; //for hash funct
	struct s_rooms	*prev; //for way building
	t_neigh			*neigh;
};

typedef struct	s_way
{
	t_rooms			*room;
	short int		ant;
	struct s_way	*next;
}				t_way;

typedef struct	s_ways
{
	t_way			*way;
	int 			depth;
	struct s_ways	*other;
}				t_ways;

typedef struct	s_data
{
	int			n_ants;
	t_rooms		*st;
	t_rooms		*end;
	int 		n_ways;
	t_ways		*ways;
	t_rooms		*rooms[100];
}				t_data;

typedef struct	s_ant
{
	int 			n_ant;
	t_way			*room;
	struct s_ant	*next;
}				t_ant;

int 	is_room(char *s);
int 	is_link(char *s);
int 	is_n_ants(char *s);

int		parse(t_data *dt);
int		add_data(int lt, t_data *dt, char *s);
t_rooms	*add_room(t_data *dt, char *name, int lt);
void	add_link(t_data *dt, char *s);

int 	have_neigh(t_rooms *room, char *name);
void	add_neigh(t_rooms *r1, t_rooms *r2);

void	find_ways(t_data *dt);
void	ways_pb(t_data *dt, t_ways *way);
void	way_pf(t_way **q, t_rooms *room);
t_way	*create_way_elem(t_rooms *room);

t_rooms	*query_pop(t_way **q);
void	query_pb(t_way **q, t_rooms *room);
void	clear_query(t_way **q);

void	handle_neigh(t_way **q, t_rooms *cur);

void	print_ways(t_data *dt);

t_ant	*handle_ants(int n_ants, int *lway, t_way **mway);

void	delete_neigh(t_neigh **neigh);
#endif
