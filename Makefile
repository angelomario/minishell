# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joandre <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 15:32:04 by joandre           #+#    #+#              #
#    Updated: 2024/10/29 08:30:11 by aquissan         ###   ########.fr        #
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
EXTERNAL = -lreadline -lncurses
RM = rm -rf
MK = mkdir -p

FILES = extra.c built_ins.c main.c\
	read_bin.c echo.c free.c exit.c unset.c\
	env.c export.c dir_errors.c
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

run: $(NAME)
	@clear
	@./$(NAME)

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

aquissan:
	clear;
	git branch;
	git checkout main && git branch && git merge $@;
	git checkout $@;
	git branch;

joandre:
	clear;
	git branch;
	git checkout master && git branch && git merge $@;
	git checkout $@;
	git branch;

pusha:  fclean
	clear;
	git branch;
	git status && git add . && git status && git commit -m"in proccess"
	git push git@github.com:angelomario/minishell.git;
