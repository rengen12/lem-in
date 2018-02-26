# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amichak <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/23 11:53:43 by amichak           #+#    #+#              #
#    Updated: 2018/01/23 12:07:30 by amichak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:		all clean fclean re $(NAME)

CFLAGS =	-Wall -Wextra -Werror
SRC =		add_data.c handle_ants.c handle_link.c handle_neigh.c \
			handle_room.c handle_way.c main.c parse.c print_ways.c query.c \
			verifer.c way_helpers.c fl_p.c
NAME =		lem-in
OBJFOLD =	obj/
LIBFT =		./libft/
LIB =		-L. libft/libft.a
HEADER =	-I ./

OBJ = $(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(SRC)))

all:		$(NAME)

$(NAME):	$(OBJ)
	@make -C $(LIBFT) -f Makefile
	gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	@echo "lem-in: done"

$(OBJFOLD)%.o:	%.c
	mkdir -p $(OBJFOLD)
	gcc $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make -C $(LIBFT) -f Makefile clean
	@rm -rf $(OBJFOLD)
	@echo "lem-in: objects cleaned"

fclean:		clean
	@make -C $(LIBFT) -f Makefile fclean
	@rm -f $(NAME)
	@echo "lem-in: binary deleted"


re:			fclean all
