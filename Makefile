# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngastana  < ngastana@student.42urduliz.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 17:47:08 by ngastana          #+#    #+#              #
#    Updated: 2024/05/04 11:43:07 by ngastana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc
CFLAGS := -Wall -Werror -Wextra -g #-fsanitize=thread

SRCS := main.c \
		utils.c \
		ft_atoi.c \
		philos_working.c \

OBJS := $(SRCS:.c=.o)

CYAN        := \033[0;36m
CURSIVE		:= \033[3m
BOLD       := \033[1m
BLACK      := \033[30m
RED        := \033[31m
GREEN      := \033[32m
YELLOW     := \033[33m
BLUE       := \033[34m
MAGENTA    := \033[35m
WHITE      := \033[37m
RESET      := \033[0m

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -o $@ -I./

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -pthread
	@echo ""
	@echo "$(BOLD) $(CURSIVE) INFORMATION ORDER: $(RESET)"
	@echo "$(BLUE) 	1. Number_of_philosophers $(RESET)"
	@echo "$(RED)  	2. Time_to_die $(RESET)"
	@echo "$(GREEN)  	3. Time_to_eat $(RESET)"
	@echo "$(WHITE)  	4. Time_to_sleep $(RESET)"
	@echo "$(BLACK)  	5. Number_of_times_each_philosopher_must_eat (optional) $(RESET)"
	@echo ""

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re