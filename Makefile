# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llalba <llalba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 14:25:58 by llalba            #+#    #+#              #
#    Updated: 2022/01/25 15:27:39 by llalba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

blue			= /bin/echo -e -n "\x1b[1m\x1b[34m$1\x1b[0m"
green			= /bin/echo -e -n "\x1b[1m\x1b[32m$1\x1b[0m"
filename		= /bin/echo -e -n "\x1b[30m\x1b[47m\x1b[1m$1\x1b[0m"

NAME			= cub3D

CC				= gcc

FLAGS			= -Wall -Werror -Wextra -pthread

HEADERS_DIR		= ./include/

SRC_DIR			= ./src/

OBJ_DIR			= ./obj/

SRC_LIST		= \
				main.c \
				gnl.c \
				utils.c

SRC				= $(SRC_LIST)

OBJ				= $(SRC:%.c=$(OBJ_DIR)%.o)

DEPS			= $(OBJ:%.o=%.d)

-include $(DEPS)

$(NAME):		$(OBJ)
				@$(call green,"Source code compiled in ")
				@$(call filename,"$(OBJ_DIR)")
				@$(call green,". ✅")
				@/bin/echo -e "\n💫 Linking..."
				@$(CC) $(FLAGS) -I $(HEADERS_DIR) -o $(NAME) $(OBJ) $(ADDONS)
				@$(call green,"Executable ")
				@$(call filename,"'$(NAME)'")
				@$(call green," successfully created. ✅")
				@/bin/echo -e "\n\n🚀 You're ready to go."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
				@mkdir -p $(OBJ_DIR)
				@echo "🏗  Compiling $<..."
				@$(CC) $(CC_FLAGS) -I $(HEADERS_DIR) -MMD -MP -c $< -o $@

all:			$(NAME)

clean:
				@/bin/echo "💦 Cleaning..."
				@rm -rf $(OBJ)
				@rm -rf $(DEPS)
				@$(call green,"Directory cleaned. ✅")
				@echo

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
