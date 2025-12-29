# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/29 11:06:18 by ludebarn          #+#    #+#              #
#    Updated: 2025/12/29 11:27:09 by ludebarn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAKEFLAGS += --no-print-directory

# Lib personelle
LIBFT = libft

# Repertoires
OBJ_DIR = object
SRC_DIR = src

# Fichiers .c
SRCS = main.c chainlist_token.c

# Chemins complets vers les fichiers source
SRC_FILES = $(addprefix $(SRC_DIR)/,$(SRCS))

# Chemins vers les fichiers objets correspondants
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Configurations de bases
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Chemins d'inclusion communs
INCLUDES = -I . -I $(LIBFT)/

# Ajouter le répertoire MLX aux includes
RL_PATH = $(shell brew --prefix readline 2>/dev/null || echo /usr)

# Bibliothèques personnelles
LIBRARY_PATH = -L$(LIBFT) -L$(RL_PATH)/lib
LIBRARIES = -lft -lreadline -lhistory

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

# Recompilation complète
re: fclean all

# Cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re bonus

