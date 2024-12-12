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

# ft_printf static library name and source files
FT_PRINTF_LIB = ft_printf.a
FT_PRINTF_SRC = ft_printf/ft_printf.c ft_printf/ft_functions.c
FT_PRINTF_OBJ = $(FT_PRINTF_SRC:.c=.o)

# Default rule: build both executables
all: $(CLIENT) $(SERVER)

# Rule to build the client executable
$(CLIENT): $(CLIENT_OBJ) $(FT_PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) $(FT_PRINTF_LIB)

# Rule to build the server executable
$(SERVER): $(SERVER_OBJ) $(FT_PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ) $(FT_PRINTF_LIB)

# Rule to build the ft_printf static library
$(FT_PRINTF_LIB): $(FT_PRINTF_OBJ)
	ar rcs $(FT_PRINTF_LIB) $(FT_PRINTF_OBJ)

# Rule to compile ft_printf source files into object files
$(FT_PRINTF_OBJ): ft_printf/ft_printf.c ft_printf/ft_functions.c
	$(CC) $(CFLAGS) -c ft_printf/ft_printf.c -o ft_printf/ft_printf.o
	$(CC) $(CFLAGS) -c ft_printf/ft_functions.c -o ft_printf/ft_functions.o

# Rule to clean object files
clean:
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ) $(FT_PRINTF_OBJ) ft_printf/ft_printf.o ft_printf/ft_functions.o

# Rule to clean object files and executables
fclean: clean
	$(RM) $(CLIENT) $(SERVER) $(FT_PRINTF_LIB)

# Rule to recompile everything
re: fclean all



