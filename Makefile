.PHONY: all clean fclean re

CXXFLAGS := -c -Wall -Wextra -Werror -I include

FILES := main.cpp OperandFactory.cpp

SRC := $(addprefix src/, $(FILES))

OBJ := $(FILES:%.cpp=obj/%.o)

NAME:= avm

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $^ -o $@

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all