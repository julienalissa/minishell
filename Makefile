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

NAME = minishell

MAKEFLAGS += --no-print-directory

# Lib personelle
LIBFT = libft

# Repertoires
OBJ_DIR = object
SRC_DIR = src

# Chemins complets vers les fichiers source
SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")

# Chemins vers les fichiers objets correspondants
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Configurations de bases
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

# Chemins d'inclusion communs
INCLUDES = -I . -I $(LIBFT)/

# Ajouter le répertoire MLX aux includes
RL_PATH = $(shell brew --prefix readline 2>/dev/null || echo /usr)

# Bibliothèques personnelles
LIBRARY_PATH = -L$(LIBFT) -L$(RL_PATH)/lib
LIBRARIES = -lft -lreadline

# Custom
COMPILE_MSG = @printf "."

# Rules
all: $(NAME)

# Compilation de l'exécutable principal
$(NAME): $(OBJS)
	$(COMPILE_MSG)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARY_PATH) $(LIBRARIES) -o $(NAME)
	@echo "\n✅ Compilation terminée pour minishell !"

# Règle pour créer les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(COMPILE_MSG)

# Nettoyage des fichiers objets
clean:
	@echo "🧹 Nettoyage des fichiers objets..."
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@make -C $(LIBFT) clean
	@echo "✅ Nettoyage terminé !"

# Nettoyage complet
fclean: clean
	@echo "🧹 Nettoyage complet..."
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo "✅ Nettoyage complet terminé !"

# Règle pour tester les leaks rapidement
leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

# Recompilation complète
re: fclean all

# Cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re bonus

