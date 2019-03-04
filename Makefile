# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 18:13:28 by abarnett          #+#    #+#              #
#    Updated: 2019/03/03 19:17:34 by alan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			ft_ls
LIB :=			libft/libftprintf.a
CC :=			gcc

SRC_DIR :=		./srcs

C_SRCS :=		$(wildcard $(SRC_DIR)/*.c)
C_OBJS :=		$(patsubst %.c,%.o,$(C_SRCS))
DEPENDS :=		$(patsubst %.c,%.d,$(C_SRCS))

INCLUDE_DIRS :=	-I./includes -I./libft/includes
CFLAGS +=		-g -Wall -Wextra -Werror $(INCLUDE_DIRS)
DEPFLAGS +=		-MMD -MT $@
LDFLAGS +=		-L./libft -lftprintf

.PHONY:			all clean fclean re

all: $(NAME)
	@ctags -R

$(LIB):
	make -C libft

$(NAME): $(LIB) $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPENDS)

clean:
	@- $(RM) $(C_OBJS)
	@- make -C libft clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C libft fclean

re: fclean all
