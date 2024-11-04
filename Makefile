# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 10:26:08 by hrasolof          #+#    #+#              #
#    Updated: 2024/09/27 18:41:10 by hrasolof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS_C = -Wall -Werror -Wextra -g  # Compilation flags
LIBS = -lreadline  # Libraries to link with

RM = rm -rf

SRCS = 	minishell.c \
		src/simple_command.c \
		src/command_handling.c \
		src/ft_token.c \
		src/execute_command.c \
		src/ft_find_path.c \
		src/ft_free.c \
		src/ft_utils.c \
		ft_remove_quote.c \
		src/create_env.c \

LIBFT_PATH = Libft
LIBFT = $(LIBFT_PATH)/libft.a

OBJS = $(SRCS:.c=.o)
TOTAL_SRCS = $(words $(SRCS))  # Total number of source files
CURRENT_OBJ_COUNT = 0

# Function to display compilation progress
define compile_message
	@$(eval CURRENT_OBJ_COUNT=$(shell echo $$(($(CURRENT_OBJ_COUNT) + 1))))
	@echo -ne "\rCompiling: " \
	"[$$(( $(CURRENT_OBJ_COUNT) * 100 / $(TOTAL_SRCS) ))% completed]\033[0m"
	@sleep 0.05
endef

# Rule for compiling .o files and updating progress
%.o: %.c
	@$(CC) $(FLAGS_C) -c $< -o $@
	@$(call compile_message)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS_C) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "\033[1;32mCompilation done!\033[0m"

all: $(NAME)

$(LIBFT) :
	@make -C $(LIBFT_PATH)

clean:
	@echo "\033[0;33mCleaning object files...\033[0m"
	@$(RM) $(OBJS)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "\033[0;33mCleaning...\033[0m"	
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

