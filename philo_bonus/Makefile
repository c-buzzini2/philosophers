# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:59:11 by cbuzzini          #+#    #+#              #
#    Updated: 2025/08/04 10:52:28 by cbuzzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = includes/

HDR_ALL = philo_bonus.h

HDR_FILES_ALL = $(addprefix $(INCLUDE_DIR), $(HDR_ALL))

SRC_FILES = main.c \
			parse_args.c \
			print.c \
			termination.c \
			semaphores.c \
			forks.c \
			start_routine.c \
			eat.c \
			sleep.c \
			utils.c \
			ft_itoa.c \
			monitors.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

CC = cc 
FLAGS = -g -Wall -Wextra -Werror
NAME = philo_bonus

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR_FILES_ALL)
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ_FILES)
	$(CC) $(FLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus
