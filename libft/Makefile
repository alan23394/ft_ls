# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarnett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/25 22:40:12 by abarnett          #+#    #+#              #
#    Updated: 2019/01/07 19:11:44 by abarnett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			libftprintf.a

INCLUDE_DIR :=	./includes
L_OBJS :=		$(patsubst %.c,%.o,$(wildcard ./srcs/*.c))
C_OBJS :=		$(patsubst %.c,%.o,$(wildcard ./srcs/ft_printf/*.c))

CFLAGS +=		-g -Wall -Wextra -Werror -I$(INCLUDE_DIR)
LDFLAGS +=		-L./ -lftprintf

.PHONY:			all clean fclean re

all: $(NAME)

$(NAME): $(L_OBJS) $(C_OBJS)
	ar rc $(NAME) $(L_OBJS) $(C_OBJS)
	ranlib $(NAME)

clean:
	@- $(RM) $(C_OBJS) $(L_OBJS)

fclean: clean
	@- $(RM) $(NAME)

re: fclean all
