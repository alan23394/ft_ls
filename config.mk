# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/24 19:28:07 by alan              #+#    #+#              #
#    Updated: 2019/03/24 19:34:32 by alan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library
LIBRARY :=		ft
LIB_NAME :=		libft.a
LIB_DIR :=		./libft
# My libft has multiple makefiles. This should be relative to LIB_DIR
LIB_MAKEFILE :=	Makefile

# Project
NAME :=			ft_ls
SRC_DIR :=		./srcs
INCLUDE_DIRS :=	./includes $(LIB_DIR)/includes

# Compiling
CC :=			gcc
CFLAGS +=		-g -Wall -Wextra -Werror $(foreach INC, $(INCLUDE_DIRS), -I$(INC))
LDFLAGS +=		-L$(LIB_DIR) -l$(LIBRARY)
