# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/25 13:18:39 by honguyen          #+#    #+#              #
#    Updated: 2024/01/11 16:11:19 by honguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CC = cc
# FLAGs = -Wall -Wextra -Werror
# RM = rm -rf
# LIBFT = libft/libft.a
# SRCS = server.c client.c
# SRCS_BONUS = server_bonus.c client_bonus.c
# OBJ = $(SRCS:.c=.o)
# OBJ_BONUS = $(SRCS_BONUS:.c=.o)

# all: client server

# client: client.o $(LIBFT)
# 	$(cc) $(FLAGS) $< libft/libft.a -o $@

# server: server.o $(LIBFT)
# 	$(cc) $(FLAGS) $< libft/libft.a -o $@

# $(LIBFT):
# 	make -C ./libft

# bonus: $(OBJ_BONUS) $(LIBFT)
# 	$(CC) $(FLAGS) client_bonus.o $(LIBFT) -o client_bonus
# 	$(CC) $(FLAGS) client_bonus.o $(LIBFT) -o server_bonus

# %.o: %.c
# 	$(CC) $(FLAGS) -c $<	

# clean: 
# 	$(RM) $(OBJ) $(OBJ_BONUS)
# 	make -C ./libft clean
	
# fclean: clean
# 	$(RM) client server client_bonus server_bonus ./libft/libft.a
	
# re: fclean all

# .PHONY: all bonus clean fclean re

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
LIBFT = libft/libft.a
SRC = client.c server.c
SRC_BNS = client_bonus.c server_bonus.c
OBJ = $(SRC:.c=.o)
OBJ_BNS = $(SRC_BNS:.c=.o)

all: client server

%.o: %.c
	$(CC) $(CFLAGS) -c $<

client: client.o $(LIBFT)
	$(CC) $(CFLAGS) $< libft/libft.a -o $@

server: server.o $(LIBFT)
	$(CC) $(CFLAGS) $< libft/libft.a -o $@

$(LIBFT):
	make -C ./libft

bonus: $(OBJ_BNS) $(LIBFT)
	$(CC) $(CFLAGS) client_bonus.o libft/libft.a -o client_bonus
	$(CC) $(CFLAGS) server_bonus.o libft/libft.a -o server_bonus

clean:
	$(RM) $(OBJ) $(OBJ_BNS)
	make -C ./libft clean

fclean: clean
	$(RM) client server client_bonus server_bonus ./libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re
