# ==============================================================================
#                                     CONFIG
# ==============================================================================

NAME        =	minishell

CC          =	cc
CFLAGS      =	-Wall -Wextra -Werror -g3 -fsanitize=address

SRC_DIR     =	src
OBJ_DIR     =	obj
INC_DIR     =	include
LIBFT_DIR   =	./libft

LIBFT       =	$(LIBFT_DIR)/libft.a
LIBS        =	-lreadline
INCLUDES    =	-I$(INC_DIR) -I$(LIBFT_DIR)

# ==============================================================================
#                                     SOURCES
# ==============================================================================

SRCS_FILES  =	main.c \
				clean.c \
				env/env_utils.c \
				lexer/lexer.c \
				lexer/lexer_separator.c \
				lexer/token_utils.c \
				parser/parser.c \
				parser/parse_pipe.c \
				parser/parser_utils.c \
				expander/expander_fill.c \
				expander/expander_len.c \
				expander/expander.c \
				expander/wildcard.c \
				execution/exec_cmd.c \
				execution/exec_logic.c \
				execution/exec_main.c \
				execution/exec_pipe.c \
				execution/exec_redir.c \
				utils/free_ast.c \
				signals/signals.c \
				builtins/builtins_utils.c \
				builtins/builtins_simple.c \
				builtins/builtins_export.c \
				builtins/export_utils.c \
				builtins/builtins_unset.c \
				builtins/builtins_cd.c \
				builtins/builtins_exit.c \


SRCS        =	$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS        =	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS     =	$(INC_DIR)/minishell.h
TOTAL_FILES =	$(words $(SRCS_FILES))

# ==============================================================================
#                                     COLORS
# ==============================================================================

RED         =	\033[0;31m
GREEN       =	\033[0;32m
YELLOW      =	\033[0;33m
CYAN        =	\033[0;36m
BOLD        =	\033[1m
RESET       =	\033[0m

# Spinner characters
SPINNER     =	⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏

# ==============================================================================
#                                     RULES
# ==============================================================================

all: $(NAME)

# Counter file for progress tracking
.compile_count:
	@echo "0" > .compile_count

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 2>&1 || (echo "\n$(RED)✗ Error compiling $<$(RESET)" && exit 1)
	@COUNT=$$(cat .compile_count 2>/dev/null || echo 0); \
	COUNT=$$((COUNT + 1)); \
	echo $$COUNT > .compile_count; \
	PERCENT=$$((COUNT * 100 / $(TOTAL_FILES))); \
	SPINNER_CHARS="⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏"; \
	SPIN_IDX=$$((COUNT % 10 + 1)); \
	SPIN_CHAR=$$(echo $$SPINNER_CHARS | cut -d' ' -f$$SPIN_IDX); \
	printf "\r$(CYAN)$$SPIN_CHAR $(YELLOW)Compiling... [$$COUNT/$(TOTAL_FILES)] $$PERCENT%%$(RESET)   "

# Linkage final
$(NAME): .compile_count $(LIBFT) $(OBJS)
	@printf "\r$(CYAN)⠿ $(YELLOW)Linking $(NAME)...$(RESET)                    \n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@rm -f .compile_count
	@echo "$(GREEN)$(BOLD)"
	@echo "  ╔═══════════════════════════════════════════╗"
	@echo "  ║   ✓ $(NAME) compiled successfully!   ║"
	@echo "  ╚═══════════════════════════════════════════╝"
	@echo "$(RESET)"

# Compilation de la Libft
$(LIBFT):
	@echo "$(CYAN)⠿ $(YELLOW)Compiling Libft...$(RESET)"
	@make bonus -C $(LIBFT_DIR) > /dev/null 2>&1

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "$(RED)✗ Object files removed.$(RESET)"; \
	fi
	@rm -f .compile_count
	@make clean -C $(LIBFT_DIR) > /dev/null 2>&1

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(RED)✗ $(NAME) removed.$(RESET)"; \
	fi
	@make fclean -C $(LIBFT_DIR) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re
