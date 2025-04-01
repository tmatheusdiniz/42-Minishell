CC = cc
LDFLAGS = -lreadline -lncurses
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = Libft/libft.a
NAME = Minishell
SRC_DIR = ./src
SRC_BUILT = $(SRC_DIR)/builtins

SRCS = $(SRC_DIR)/main.c $(SRC_BUILT)/echo.c $(SRC_BUILT)/pwd.c $(SRC_BUILT)/cd.c $(SRC_BUILT)/env.c \
	$(SRC_BUILT)/unset.c $(SRC_DIR)/errors/errors_utils.c $(SRC_DIR)/utils/utils.c

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
