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
				lexer.c \
				lexer_separator.c \
				parser.c \
				parse_pipe.c \
				parser_utils.c \
				token_utils.c

SRCS        =	$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS        =	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS     =	$(INC_DIR)/minishell.h

# ==============================================================================
#                                     COLORS
# ==============================================================================

RED         =	\033[0;31m
GREEN       =	\033[0;32m
YELLOW      =	\033[0;33m
CYAN        =	\033[0;36m
RESET       =	\033[0m

# ==============================================================================
#                                     RULES
# ==============================================================================

all: $(NAME)

# Creation du dossier obj si inexistant
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(CYAN)Creating object directory...$(RESET)"

# Compilation des objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Linkage final
$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Compilation de la Libft
$(LIBFT):
	@echo "Compiling Libft..."
	@make bonus -C $(LIBFT_DIR)

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "$(RED)Object files removed.$(RESET)"; \
	fi
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(RED)$(NAME) removed.$(RESET)"; \
	fi
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
