NAME		:= push_swap
CC			:= cc
CFLAGS		= -Wall -Wextra -Werror -g3

LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS		:= \
	$(wildcard src/*.c) \
	$(wildcard src/init/*.c) \
	$(wildcard src/moves/*.c) \
	$(wildcard src/lis/*.c)
INCLUDES	:= -I. -I$(LIBFT_DIR)

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

BONUS_NAME	:= checker
BONUS_SRCS	:= \
	$(wildcard bonus/*.c) \
	$(wildcard src/init/*.c) \
	$(wildcard src/moves/*.c) \
	src/debug_print.c
BONUS_OBJS	:= $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

TESTER_DIR	:= tester_SimonCROS
TESTER_NAME	:= complexity
TESTER_BIN	:= $(TESTER_DIR)/$(TESTER_NAME)
TEST_ITER	:= 1000
TEST1_ARGC	:= 100
TEST1_MAX	:= 700
TEST2_ARGC	:= 500
TEST2_MAX	:= 5500

VIS_BIN		:= push_swap_visualizer/build/bin/visualizer

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)

test: re
	@$(MAKE) -C $(TESTER_DIR) fr
	@echo "\n----------"
	@./$(TESTER_BIN) $(TEST1_ARGC) $(TEST_ITER) $(TEST1_MAX) || true
	@echo "\n----------"
	@./$(TESTER_BIN) $(TEST2_ARGC) $(TEST_ITER) $(TEST2_MAX)

vis: re
	@$(VIS_BIN)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus test clean fclean re