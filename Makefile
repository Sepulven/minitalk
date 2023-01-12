# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 15:01:23 by asepulve          #+#    #+#              #
#    Updated: 2023/01/05 16:59:29 by asepulve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Minitalk
CFLAGS 		= -Wall -Wextra -Werror
CC		= gcc
CSRC		= client.c
SSRC		= server.c
LIBFT		= ./libft/libft.a
RM		= rm -f
OBJECTS		= $(SRC:.c=.o)

$(NAME): server client

all: server client

bonus:  server client

libft:
		@make -C ./libft

server: libft server.o
		@${CC} ${CFLAGS} server.o ${LIBFT} -o server

client: libft client.o
		@${CC} ${CFLAGS} client.o ${LIBFT} -o client

clean:
		@${RM} server.o client.o
		@make clean -C ./libft
fclean: clean
		@make fclean -C ./libft
		@${RM} client server
re: fclean ${NAME}

.PHONY: all $(NAME) clean fclean client server re libft
