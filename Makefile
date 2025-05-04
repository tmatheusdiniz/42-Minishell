CC = cc
LDFLAGS = -lreadline -lncurses
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = Lib/Libft/libft.a
NAME = Minishell
SRC_DIR = ./srcs
SRC_BUILT = $(SRC_DIR)/builtins

SRCS = 	$(SRC_DIR)/core/main.c $(SRC_BUILT)/echo.c $(SRC_BUILT)/pwd.c $(SRC_BUILT)/cd.c $(SRC_BUILT)/env.c \
		$(SRC_BUILT)/unset.c $(SRC_DIR)/errors/errors_utils.c $(SRC_DIR)/utils/utils.c $(SRC_DIR)/signals/signals.c \
		$(SRC_DIR)/utils/free.c $(SRC_DIR)/parsing/parsing.c $(SRC_DIR)/parsing/expand.c $(SRC_DIR)/tokenization/split_token.c\
		$(SRC_DIR)/tokenization/tokenizer.c	$(SRC_DIR)/tree/tree.c $(SRC_DIR)/tree/tree_utils.c  
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
