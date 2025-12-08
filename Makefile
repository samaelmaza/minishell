NAME        = minishell
CC          = cc
# 1. On retire -lreadline d'ici
CFLAGS      = -Wall -Wextra -Werror -g -g3 -fsanitize=address

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

# 2. On crée une variable pour les librairies
# (Note: Sur Linux -lreadline suffit, sur Mac 42 il faut souvent les chemins -L...)
LIBS        = -lreadline

# 3. Correction des includes (Ajout du -I devant LIBFT_DIR)
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)

RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m
RESET       = \033[0m

SRCS        = $(SRC_DIR)/main.c $(SRC_DIR)/clean.c $(SRC_DIR)/lexer.c $(SRC_DIR)/lexer_separator.c $(SRC_DIR)/token_utils.c
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS     = $(INC_DIR)/minishell.h

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(CYAN)Creating object directory...$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 4. Correction de l'ordre de compilation
# $(LIBS) est mis tout à la fin
$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# 5. Appel de 'bonus' pour avoir ft_lstnew (si ton Makefile Libft a une règle bonus)
$(LIBFT):
	@echo "Compilation de la Libft..."
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

.PHONY: all clean fclean re help
