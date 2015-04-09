.PHONY: all clean fclean re

CXXFLAGS := -std=c++11 -c -Wall -Wextra -Werror -Wno-deprecated-register -I include

FILES := main.cpp OperandFactory.cpp Lexer.cpp Parser.cpp tokens.cpp

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
	@mkdir -p "misc/output"
	@i=1
	@echo "\n\033[1;33m\033[4;33mLaunching unit tests for abstract VM...\n\033[0m"
	@for d in misc/tests/* ; do \
		echo "$$i - Running test file \"$$d\":" ; \
		ruby $$d ; \
		i=$$(($$i+1)) ; \
		echo "" ; \
	done
	@echo "\033[1;33m\033[4;33mDone.\n\033[0m"

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all
