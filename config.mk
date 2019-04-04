# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/24 19:28:07 by alan              #+#    #+#              #
#    Updated: 2019/03/29 20:55:38 by alan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library
LIBRARY :=		ft
LIB_NAME :=		libft.a
LIB_DIR :=		./libft
# My libft has multiple makefiles. This should be relative to LIB_DIR
LIB_MAKEFILE :=	Makefile
LIB_SRCS :=		$(shell find $(LIB_DIR) -name "*.c")

# Project
NAME :=			ft_ls
SRC_DIR :=		./srcs
INCLUDE_DIRS :=	./includes $(LIB_DIR)/includes

# Compiling
CC :=			gcc
CFLAGS +=		-g -Wall -Wextra -Werror $(foreach INC, $(INCLUDE_DIRS), -I$(INC))
LDFLAGS +=		-L$(LIB_DIR) -l$(LIBRARY) -lacl
