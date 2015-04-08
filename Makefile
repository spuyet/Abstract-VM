.PHONY: all clean fclean re

CXXFLAGS := -std=c++11 -c -Wall -Wextra -Werror -Wno-deprecated-register -I include

FILES := main.cpp OperandFactory.cpp Operand.cpp Lexer.cpp Parser.cpp tokens.cpp

LEXER := tokens.l

SRC := $(addprefix src/, $(FILES))

OBJ := $(FILES:%.cpp=obj/%.o)

TOKENS := $(LEXER:%.l=src/%.cpp)

NAME:= avm

all: $(NAME)

$(NAME): $(TOKENS) $(OBJ)
	$(CXX) $(OBJ) -o $@

src/%.cpp: flex/%.l
	flex -o src/tokens.cpp flex/$(LEXER)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $< -o $@

tests:
	mkdir -p "misc/output"
	i=1
	for d in misc/tests/* ; do \
		echo "$$i - Running test file \"$$d\":\n" \
		ruby $$d ; \
		i=$$(($$i+1)) ; \
		echo "" ; \
	done

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all