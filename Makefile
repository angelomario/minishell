# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joandre <joandre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 15:32:04 by joandre           #+#    #+#              #
#    Updated: 2024/12/11 00:14:50 by joandre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# DIRECTORIES	
DIR = sources
LIB = libft.a
DIR_OBJ = objects
DIR_LIB = libft
INCLUDES = includes
# FLAGS
CC = cc 
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -fsanitize=address -g
EXTERNAL = -lreadline -lncurses
RM = rm -rf
MK = mkdir -p

FILES = extra.c main.c aux_redir.c aux_redir2.c expanded.c\
	read_bin.c echo.c free.c exit.c unset.c utils3.c utils4.c\
	env.c export.c aux_export.c heredoc.c strsplit.c\
	pipe.c pwd.c cd.c signals.c redirect.c parse.c utils.c utils2.c
SRC = $(addprefix $(DIR)/, $(FILES))
SRC_OBJ = $(addprefix $(DIR_OBJ)/, $(FILES:.c=.o))

# RULES
all: $(DIR_LIB)/$(LIB) $(NAME)

$(DIR_LIB)/$(LIB):
	@make -C $(DIR_LIB)

$(NAME): $(DIR_LIB)/$(LIB) $(SRC_OBJ)
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(SRC_OBJ) -o $(NAME) -L./$(DIR_LIB) -lft $(EXTERNAL) 

$(DIR_OBJ)/%.o: $(DIR)/%.c
	@$(MK) $(DIR_OBJ)
	@$(CC) -I$(INCLUDES) $(CFLAGS) -L$(DIR_LIB) -lft -c $< -o $@

run: re $(NAME)
	@clear
	@./$(NAME)

run_leak: re $(NAME)
	@clear
	@valgrind -s --leak-check=full ./$(NAME)

clean:
	make clean -C $(DIR_LIB)
	$(RM) $(SRC_OBJ)
	$(RM) $(DIR_OBJ)

fclean: clean
	make fclean -C $(DIR_LIB)
	$(RM) $(NAME)

re: fclean all

push: fclean
	clear;
	git branch;
	git status && git add * && git status && git commit -m"in proccess" && git push;

