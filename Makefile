NAME		:= push_swap
CC			:= cc
CFLAGS		= -Wall -Wextra -Werror -O2 -g3 -fsanitize=address

LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS		:= \
	$(wildcard src/*.c) \
	$(wildcard src/*/*.c) \
	$(wildcard src/*/*/*.c)
INCLUDES	:= \
	-I$(LIBFT_DIR) \
	-Isrc/1_args \
	-Isrc/2_stack \
	-Isrc/3_moves \
	-Isrc/4_state \
	-Isrc/5_config \
	-Isrc/6_algos \
	-Isrc/6_algos/1_sort_three \
	-Isrc/6_algos/2_naive \
	-Isrc/6_algos/3_chunk \
	-Isrc/6_algos/4_k_sort \
	-Isrc/6_algos/5_greedy \
	-Isrc/6_algos/6_finish \
	-Isrc/7_optis/1_median \
	-Isrc/7_optis/2_lis \
	-Isrc/7_optis/3_swap

OBJ_DIR		:= obj
OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

BONUS_NAME	:= checker
BONUS_SRCS	:= \
	$(wildcard bonus/*.c) \
	$(wildcard src/init/*.c) \
	$(wildcard src/moves/*.c) \
	src/debug_print.c
BONUS_OBJS	:= $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

MY_TESTER	:= ./tests/test.sh

TESTER_DIR	:= tester_SimonCROS
TESTER_NAME	:= complexity
TESTER_BIN	:= $(TESTER_DIR)/$(TESTER_NAME)
TEST_ITER	:= 1000
TEST1_ARGC	:= 100
TEST1_MAX	:= 700
TEST2_ARGC	:= 500
TEST2_MAX	:= 5500
TEST_OPT	:= -s 3321135322

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
	@$(MY_TESTER)
	@$(MAKE) -C $(TESTER_DIR) fr
	@echo "\n----------"
	@./$(TESTER_BIN) $(TEST_OPT) $(TEST1_ARGC) $(TEST_ITER) $(TEST1_MAX) || true
	@echo "\n----------"
	@./$(TESTER_BIN) $(TEST_OPT) $(TEST2_ARGC) $(TEST_ITER) $(TEST2_MAX)

vis: re
	@$(VIS_BIN)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus test clean fclean re