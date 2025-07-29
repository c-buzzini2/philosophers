# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:59:11 by cbuzzini          #+#    #+#              #
#    Updated: 2025/07/29 17:43:14 by cbuzzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = includes/

HDR_ALL = philo.h
#HDR_BONUS = philo_bonus.h

HDR_FILES_ALL = $(addprefix $(INCLUDE_DIR), $(HDR_ALL))
#HDR_FILES_BONUS = $(addprefix $(INCLUDE_DIR), $(HDR_BONUS))

SRC_FILES = main.c \
			parse_args.c \
			print.c \
			termination.c \
			mutexes.c \
			threads.c \
			start_routine.c \
			prepare_to_eat.c \
			eat.c \
			sleep.c \
			monitor.c \
			utils.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

#BONUS_FILES = 

#BONUS = $(addprefix $(SRC_DIR), $(BONUS_FILES))
#OBJ_BONUS = $(addprefix $(OBJ_DIR)bonus_, $(BONUS_FILES:.c=.o))

CC = cc 
FLAGS = -g -Wall -Wextra -Werror #-lpthread
NAME = philo

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR_FILES_ALL)
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -c $< -o $@

#$(OBJ_DIR)bonus_%.o: $(SRC_DIR)%.c $(HDR_FILES_BONUS)
#	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -DBONUS -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	$(CC) $(FLAGS) $(OBJ_FILES) -o $(NAME)

#bonus: $(OBJ_DIR) $(OBJ_BONUS)
#	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus

#valgrind --leak-check=full --show-leak-kinds=all --tool=helgrind --trace-children=yes
#strace -f -e trace=clone ./philo 5 200 200 200