# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 18:13:28 by abarnett          #+#    #+#              #
#    Updated: 2019/08/05 15:11:30 by abarnett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Configuration is done in config.mk, you shouldn't need to edit this file!

# Includes all needed variables
include config.mk

C_SRCS :=		$(wildcard $(SRC_DIR)/*.c)
C_OBJS :=		$(patsubst %.c,%.o,$(C_SRCS))
DEPENDS :=		$(patsubst %.c,%.d,$(C_SRCS))
DEPFLAGS +=		-MMD -MT $@

MAKE_LIBRARY :=	make -C $(LIB_DIR) -f $(LIB_MAKEFILE) --no-print-directory
LIB :=			$(LIB_DIR)/$(LIB_NAME)

.PHONY:			all clean fclean re

all: tags $(NAME)

tags: $(C_SRCS) $(LIB_SRCS)
	@- ctags -R

$(LIB): $(LIB_SRCS)
	@ $(MAKE_LIBRARY)

$(NAME): $(LIB) $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) -o $(NAME) $(LDFLAGS)

systemlibft: $(C_OBJS)
	$(CC) $(CFLAGS) $(C_OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPENDS)

clean:
#	@- $(MAKE_LIBRARY) clean
	@- $(RM) $(C_OBJS) $(DEPENDS)

fclean: clean
#	@- $(MAKE_LIBRARY) fclean
	@- $(RM) $(NAME)

re: fclean all

libclean:
	@- $(MAKE_LIBRARY) fclean
