# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucasdebarnot <lucasdebarnot@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/29 11:06:18 by ludebarn          #+#    #+#              #
#    Updated: 2026/01/10 16:57:28 by lucasdebarn      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
DEPFLAGS	= -MMD -MP

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBFT_DIR	= libft

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)

SRC_FILES   = $(SRC_DIR)/main.c \
			$(SRC_DIR)/utils/utils1.c \
			$(SRC_DIR)/utils/signals.c \
			$(SRC_DIR)/tokenization/tokenization_utils2.c \
			$(SRC_DIR)/tokenization/tokenization_utils.c \
			$(SRC_DIR)/tokenization/tokenization.c \
			$(SRC_DIR)/tokenization/clear_token.c \
			$(SRC_DIR)/execution/exec_utils2.c \
			$(SRC_DIR)/execution/exec_utils.c \
			$(SRC_DIR)/execution/exec_redir_hd.c \
			$(SRC_DIR)/execution/exec_redir.c \
			$(SRC_DIR)/execution/exec_operator.c \
			$(SRC_DIR)/execution/exec_ast.c \
			$(SRC_DIR)/envp/envp_utils.c \
			$(SRC_DIR)/envp/envp.c \
			$(SRC_DIR)/envp/chainlist_env.c \
			$(SRC_DIR)/builtin/unset.c \
			$(SRC_DIR)/builtin/pwd.c \
			$(SRC_DIR)/builtin/export_utils.c \
			$(SRC_DIR)/builtin/export.c \
			$(SRC_DIR)/builtin/exit_42.c \
			$(SRC_DIR)/builtin/execut_builtin.c \
			$(SRC_DIR)/builtin/env.c \
			$(SRC_DIR)/builtin/echo.c \
			$(SRC_DIR)/builtin/cd.c \
			$(SRC_DIR)/builtin/builtin.c \
			$(SRC_DIR)/ast/node_ast_utils.c \
			$(SRC_DIR)/ast/node_ast_redir.c \
			$(SRC_DIR)/ast/node_ast.c \
			$(SRC_DIR)/ast/expand_wildcard.c \
			$(SRC_DIR)/ast/expand_dollar.c \
			$(SRC_DIR)/ast/build_ast.c \
			$(SRC_DIR)/ast/ast_utils.c \
			$(SRC_DIR)/ast/ast.c

OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEPS		= $(OBJS:.o=.d)

LIBRARIES	= -lreadline -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBRARIES) -o $(NAME)
	@echo "\n✅ Compilation terminée pour minishell !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

-include $(DEPS)

leaks: $(NAME)
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re
