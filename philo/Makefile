# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 17:45:28 by diolivei          #+#    #+#              #
#    Updated: 2024/11/18 16:00:18 by diolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Aliases
RESET = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

cc = CC
CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard src/*.c)
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

NAME = philo

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@echo "$(MAGENTA)- Compiling...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "$(GREEN)- Project compiled!$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)- Removed object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)- Removed executable.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
