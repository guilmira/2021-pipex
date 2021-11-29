# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 13:08:33 by guilmira          #+#    #+#              #
#    Updated: 2021/11/29 11:51:55 by guilmira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ARGS = 1files/infile.txt "ls -l" "wc -l" 1files/outfile.txt
#ARGS = 1files/infile.txt "ls -l" "grep drw" "wc -l" 1files/outfile.txt
ARGS = "<" 1files/infile.txt "ls -la" "grep drw" "wc -l" 1files/outfile.txt
#Shell command: 	$> 		 < file1 command1 | command2 > file2
#Is equivalent to: 	$> ./pipex file1 command1 command2 file2
#--------------------------------------------------------------------------------------------------------------COMPILER
NAME		= pipex
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
#--------------------------------------------------------------------------------------------------------------LIBS
LIB_DIR		= libft_submodule
LIB			= $(LIB_DIR)/libft.a
INCLUDES	= -I ./0includes -I ./libft_submodule/0includes
#--------------------------------------------------------------------------------------------------------------SOURCES
SRCS		=	pipex.c 0parser.c 0reader.c 0type.c \
				1parent.c 2son.c 4auxiliar.c
OBJS		=	$(SRCS:.c=.o)
#--------------------------------------------------------------------------------------------------------------RULES
all: $(LIB) $(NAME)

$(LIB):
	@make -C $(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB) $(INCLUDES_LIBX) -o $(NAME)
	@echo $(GREEN) "$(NAME) compiled" $(NONE)

exe: $(NAME)
	#rm 1files/outfile.txt
	./$(NAME) $(ARGS)

norm:
	norminette $(SRCS)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIB_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
#--------------------------------------------------------------------------------------------------------------FORMAT
NONE='\033[0m'
GREEN='\033[1;32m'
