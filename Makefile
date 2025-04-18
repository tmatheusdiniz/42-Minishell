<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 17:26:18 by mreinald          #+#    #+#              #
#    Updated: 2025/04/05 17:42:41 by mreinald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
RED		= \033[0;31m
GREEN	= \033[0;32m
BLUE	= \033[0;34m
D_BLUE	= \033[34m
WHITE	= \033[0;37m
YELLOW	= \033[0;33m
MAGENTA	= \033[0;35m
CYAN	= \033[3;36m
RESET	= \033[0m

#Program's name
NAME		= bin/minishell
=======
CC = cc
LDFLAGS = -lreadline -lncurses
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = Lib/Libft/libft.a
NAME = Minishell
SRC_DIR = ./srcs
SRC_BUILT = $(SRC_DIR)/builtins

SRCS = 	$(SRC_DIR)/core/main.c $(SRC_BUILT)/echo.c $(SRC_BUILT)/pwd.c $(SRC_BUILT)/cd.c $(SRC_BUILT)/env.c \
		$(SRC_BUILT)/unset.c $(SRC_DIR)/errors/errors_utils.c $(SRC_DIR)/utils/utils.c $(SRC_DIR)/signals/signals.c \
		$(SRC_DIR)/utils/free.c
OBJS = $(SRCS:.c=.o)
>>>>>>> 08127014cf98e6532efbcb8d8a966a35efa88dc0

# Commands/flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -lreadline -lncurses
INCLUDES	= -I ./include -I ./lib/Libft/include

# Directories
SRC_DIR		= srcs
OBJ_DIR		= objs
BIN_DIR		= bin
LIBFT_DIR	= ./lib/Libft/
BONUS_DIR   = bonus

# Find Sources code
SRCS		= $(wildcard $(SRC_DIR)/*/*.c)
OBJS		= $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.c=.o))

# Bonus part
BONUS_SRCS	= $(wildcard $(BONUS_DIR)/*.c)
BONUS_OBJS	= $(patsubst $(BONUS_DIR)/%.c,$(OBJ_DIR)/bonus/%.o,$(BONUS_SRCS))

# Libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L./$(LIBFT_DIR) -lft

# ASCII Art
define ART
$(MAGENTA) ${D_BLUE}
	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗
	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║
	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║
	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║
	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
  $(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[$(RESET)Made by $(BLUE)@tmatheusdiniz and @carlos$(CYAN)]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)
endef
export ART

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) $(LIBFT_FLAGS) -o $(NAME)
	@clear
	@echo "$$ART"
	@echo "$(CYAN)minishell compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@sleep 0.02
	@clear
	@echo "$(RED)Compiling minishell sources $<$(RESET)"

$(LIBFT):
	@make --silent -C $(LIBFT_DIR)

clean:
	@clear
	@make --silent -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@clear
	@make --silent -C $(LIBFT_DIR) fclean
	@rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean bonus re re_bonus
