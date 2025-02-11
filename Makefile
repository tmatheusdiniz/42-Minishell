CC = cc
LDFLAGS = -lreadline -lncurses
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = Libft/libft.a
NAME = Minishell
SRC_DIR = ./src

SRCS = $(SRC_DIR)/main.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C Libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -rf $(OBJS) Libft/*.o 

fclean: clean
	@rm -rf $(NAME)
	@echo "ALL CLEAR"

re: fclean all
