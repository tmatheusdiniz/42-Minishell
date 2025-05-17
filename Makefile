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

# Program's name
NAME		= bin/minishell

# Directories
SRC_DIR		= ./srcs
OBJ_DIR		= objs
BIN_DIR		= bin
LIBFT_DIR	=./lib

# Compiler and Flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Iincludes
IFLAGS		= -Iincludes/ -I${LIBFT_DIR}/src
INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include -I/usr/include/readline
LDFLAGS		= -L/lib/x86_64-linux-gnu -lreadline -lncurses

# Sources and Objects
SRCS		= $(wildcard $(SRC_DIR)/*/*.c)
OBJS		= $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.c=.o))

# Libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

# Handle different OS configurations for readline
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    INCLUDE += -lhistory
    READLINE =
else ifeq ($(UNAME), Darwin)
    INCLUDE = -L${LIBFT_DIR}/src -lft -L/opt/homebrew/opt/readline/lib -lreadline
    READLINE = -I/opt/homebrew/opt/readline/include
endif

# Valgrind Suppression
VALGRIND_SUPP	= valgrind_suppression.supp

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
all: submodule $(NAME)

submodule:
	@git submodule update --init --recursive

$(NAME): $(LIBFT) $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)
	@clear
	@echo "$$ART"
	@echo "$(CYAN)minishell compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) $(IFLAGS) -c $< -o $@
	@sleep 0.02
	@clear
	@echo "$(RED)Compiling minishell sources $<$(RESET)"

$(LIBFT):
	@make --silent -C $(LIBFT_DIR)

$(VALGRIND_SUPP):
	@echo "{" > $(VALGRIND_SUPP)
	@echo "   readline_memory_leak_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:readline" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   readline_memory_leak_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:add_history" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   readline_memory_leak_suppression" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   fun:_rl_*" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "{" >> $(VALGRIND_SUPP)
	@echo "   suppress_execve_bin_error" >> $(VALGRIND_SUPP)
	@echo "   Memcheck:Leak" >> $(VALGRIND_SUPP)
	@echo "   ..." >> $(VALGRIND_SUPP)
	@echo "   obj:/usr/bin/*" >> $(VALGRIND_SUPP)
	@echo "}" >> $(VALGRIND_SUPP)
	@echo "$(GREEN)Valgrind suppression file created!$(RESET)"

valgrind: $(NAME) $(VALGRIND_SUPP)
	@echo "$(YELLOW)Running valgrind with suppression file...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./$(VALGRIND_SUPP) $(NAME)

clean:
	@clear
	@make --silent -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@rm -f $(VALGRIND_SUPP)

fclean: clean
	@make --silent -C $(LIBFT_DIR) fclean
	@rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re submodule
