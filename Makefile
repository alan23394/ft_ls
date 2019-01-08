# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 18:13:28 by abarnett          #+#    #+#              #
#    Updated: 2019/01/07 19:11:35 by abarnett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			ft_ls
LIB :=			libft/libftprintf.a

C_OBJS :=		$(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

INCLUDE_DIRS :=	-I./includes -I./libft/includes
CFLAGS +=		-g -Wall -Wextra -Werror $(INCLUDE_DIRS)
LDFLAGS +=		-L./libft -lftprintf

.PHONY:			all clean fclean re

all: $(LIB) $(NAME)

$(LIB):
	make -C libft

$(NAME): $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) -o $(NAME) $(LDFLAGS)

clean:
	@- $(RM) $(C_OBJS)
	@- make -C libft clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C libft fclean

re: fclean all
