# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ludebarn <ludebarn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 09:44:49 by lucasdebarn       #+#    #+#              #
#    Updated: 2025/12/29 11:22:58 by ludebarn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
RM = rm -rf

OBJ_DIR = object
INCLUDES = -I includes -I .

COMPILE_MSG = @printf "."

# Sources
SRCS = \
	char_checker/ft_isalnum.c \
	char_checker/ft_isalpha.c \
	char_checker/ft_isascii.c \
	char_checker/ft_isdigit.c \
	char_checker/ft_isprint.c \
	char_checker/ft_tolower.c \
	char_checker/ft_toupper.c \
	convert/ft_atof.c \
	convert/ft_atoi.c \
	convert/ft_atol.c \
	convert/ft_ftoa.c \
	convert/ft_itoa.c \
	mem/ft_bzero.c \
	mem/ft_calloc.c \
	mem/ft_memchr.c \
	mem/ft_memcmp.c \
	mem/ft_memcpy.c \
	mem/ft_memmove.c \
	mem/ft_memset.c \
	printf/ft_printf.c \
	printf/ft_putalpha.c \
	printf/ft_putfloat.c \
	printf/ft_putnbr_base.c \
	str/ft_split.c \
	str/ft_strchr.c \
	str/ft_strdup.c \
	str/ft_striteri.c \
	str/ft_strjoin.c \
	str/ft_strlcat.c \
	str/ft_strlcpy.c \
	str/ft_strlen.c \
	str/ft_strmapi.c \
	str/ft_strncmp.c \
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_strtrim.c \
	str/ft_substr.c \
	str/ft_strcmp.c \
	with_fd/ft_putchar_fd.c \
	with_fd/ft_putendl_fd.c \
	with_fd/ft_putnbr_fd.c \
	with_fd/ft_putstr_fd.c \
	lst/ft_lstadd_back_bonus.c \
	lst/ft_lstadd_front_bonus.c \
	lst/ft_lstclear_bonus.c \
	lst/ft_lstdelone_bonus.c \
	lst/ft_lstiter_bonus.c \
	lst/ft_lstlast_bonus.c \
	lst/ft_lstmap_bonus.c \
	lst/ft_lstnew_bonus.c \
	lst/ft_lstsize_bonus.c\
	with_fd/ft_error.c \
	with_fd/ft_split_clear.c

# Objets correspondants (mappage .c -> object/dir/file.o)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Règles
.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

# Règle générique : object/dir/file.o <- dir/file.c
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(COMPILE_MSG)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
