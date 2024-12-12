# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msantos <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 15:14:08 by msantos           #+#    #+#              #
#    Updated: 2024/12/12 15:14:11 by msantos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g

# Names of the executables
CLIENT = client
SERVER = server

# Source files for client and server
CLIENT_SRC = client.c utils.c
SERVER_SRC = server.c utils.c

# Object files for client and server
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

# Default rule: build both executables
all: $(CLIENT) $(SERVER)

# Rule to build the client executable
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ)

# Rule to build the server executable
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ)

# Rule to clean object files
clean:
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)

# Rule to clean object files and executables
fclean: clean
	$(RM) $(CLIENT) $(SERVER)

# Rule to recompile everything
re: fclean all
