NAME		:= push_swap
CC			:= cc
CFLAGS		= -Wall -Wextra -Werror -g3

LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS		:= \
	$(wildcard src/*.c) \
	$(wildcard src/1_args/*.c) \
	$(wildcard src/2_stack/*.c) \
	$(wildcard src/3_moves/*.c) \
	$(wildcard src/4_k_sort/*.c) \
	$(wildcard src/5_greedy/*.c) \
	$(wildcard src/6_finish/*.c)
INCLUDES	:= \
	-I$(LIBFT_DIR) \
	-Isrc/1_args \
	-Isrc/2_stack \
	-Isrc/3_moves \
	-Isrc/4_k_sort \
	-Isrc/5_greedy \
	-Isrc/6_finish

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

BONUS_NAME	:= checker
BONUS_SRCS	:= \
	$(wildcard bonus/*.c) \
	$(wildcard src/init/*.c) \
	$(wildcard src/moves/*.c) \
	src/debug_print.c
BONUS_OBJS	:= $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

PARS_TESTER	:= ./tests/test_parsing.sh
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
	@$(PARS_TESTER)
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