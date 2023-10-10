
.PHONY: all re clean fclean

# Program name
NAME	= bureaucrat

# Compiler
CC		= c++
CFLAGS	= -Werror -Wextra -Wall -g -std=c++98

# Build files
INC_PATH	= ./incs/
INC			= -I $(INC_PATH)

SRC_PATH	= ./srcs/
SRC			= $(wildcard $(SRC_PATH)*.cpp)
OBJ_PATH	= ./objs/
OBJ			= $(SRC:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)

# Build rule
all: $(OBJ_PATH) $(NAME)

# Object-building rules
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Program-building rule
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(INC)

# Cleaning rules
clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

# Remake
re: fclean all
