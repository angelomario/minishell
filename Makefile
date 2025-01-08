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
NAME_BONUS = minishell_bonus

# DIRECTORIES	
DIR = sources
LIB = libft.a
DIR_OBJ = objects
DIR_LIB = libft
INCLUDES = includes

# DIRECTORIES BONUS	
DIR_B = sources_bonus
DIR_OBJ_B = objects_bonus
INCLUDES_B = includes

# FLAGS
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
EXTERNAL = -lreadline -lncurses
RM = rm -rf
MK = mkdir -p

FILES = extra.c main.c aux_redir.c aux_redir2.c expanded.c\
	read_bin.c echo.c free.c exit.c unset.c utils3.c utils4.c\
	env.c export.c aux_export.c heredoc.c strsplit.c ft_extra.c\
	pipe.c pwd.c cd.c signals.c redirect.c parse.c utils.c utils2.c\
	permissions.c

FILES_B = aux_export_bonus.c exit_bonus.c heredoc_bonus.c read_bin_bonus.c utils3_bonus.c\
	aux_redir2_bonus.c expanded_bonus.c main_bonus.c redirect_bonus.c utils4_bonus.c\
	aux_redir_bonus.c export_bonus.c parse_bonus.c signals_bonus.c utils_bonus.c\
	cd_bonus.c extra_bonus.c permissions_bonus.c strsplit_bonus.c\
	echo_bonus.c free_bonus.c pipe_bonus.c unset_bonus.c\
	env_bonus.c ft_extra_bonus.c pwd_bonus.c utils2_bonus.c\

SRC = $(addprefix $(DIR)/, $(FILES))
SRC_OBJ = $(addprefix $(DIR_OBJ)/, $(FILES:.c=.o))

SRC_B = $(addprefix $(DIR_B)/, $(FILES_B))
SRC_OBJ_B = $(addprefix $(DIR_OBJ_B)/, $(FILES_B:.c=.o))

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
	@valgrind --leak-check=full -s --show-leak-kinds=all --suppressions=leak_supression.supp ./$(NAME)

clean:
	make clean -C $(DIR_LIB)
	$(RM) $(SRC_OBJ)
	$(RM) $(DIR_OBJ)
	$(RM) $(SRC_OBJ_B)
	$(RM) $(DIR_OBJ_B)

fclean: clean
	make fclean -C $(DIR_LIB)
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

# RULES BONUS

bonus: $(DIR_LIB)/$(LIB) $(NAME_BONUS)

$(NAME_BONUS): $(DIR_LIB)/$(LIB) $(SRC_OBJ_B)
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(SRC_OBJ_B) -o $(NAME_BONUS) -L./$(DIR_LIB) -lft $(EXTERNAL)

$(DIR_OBJ_B)/%.o: $(DIR_B)/%.c
	@$(MK) $(DIR_OBJ_B)
	@$(CC) -I$(INCLUDES) $(CFLAGS) -L$(DIR_LIB) -lft -c $< -o $@

push: fclean
	clear;
	git branch;
	git status && git add * && git status && git commit -m"in proccess" && git push;

