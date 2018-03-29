# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skholodn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/04 14:31:01 by skholodn          #+#    #+#              #
#    Updated: 2017/11/04 14:31:41 by skholodn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

CC = clang++

CPPFLAGS = -std=c++11 -Wall -Wextra -Werror 

SRC = 	main.cpp \
		Parse.cpp \
		Int8.cpp \
		Int16.cpp \
		Int32.cpp \
		Float.cpp \
		Double.cpp \
		OperandFactory.cpp \
		AbstractVM.cpp


OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
