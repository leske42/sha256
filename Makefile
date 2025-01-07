NAME = tiny_sha
TEST_NAME = unit
CXX = c++
CXX1 = g++
CXX2 = clang++
CXXFLAGS = -Wall -Werror -Wextra -Wshadow #-g

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES = hash

SRC = $(addsuffix .cpp, $(SRC_FILES))

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o : %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(CXX) $(CXXFLAGS) $(OBJ) -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

$(TEST_NAME): $(OBJ) testing.o $(HEADER)
	$(CXX) $(CXXFLAGS) $(OBJ) testing.o -g -o $(TEST_NAME)

test:
	@$(MAKE) fclean > /dev/null
	@$(MAKE) $(TEST_NAME) CXXFLAGS="$(CXXFLAGS) -DTEST_MODE=1" > /dev/null
	@./unit
	@$(MAKE) fclean > /dev/null

clean:
	rm -f $(OBJ) testing.o

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

strict:
	@echo "$(GREEN)Compiling with $(YELLOW)$(CXX1)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CXX=$(CXX1)
	@echo "$(GREEN)Cleaning up...$(DEF_COLOR)"
	@$(MAKE) fclean
	@echo "$(GREEN)Compiling with $(YELLOW)$(CXX2)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CXX=$(CXX2)
	@echo "$(GREEN)Cleaning up again...$(DEF_COLOR)"
	@$(MAKE) clean
	@echo "$(GREEN)Tested for both compilers.$(DEF_COLOR)"

.PHONY: all clean fclean re asif strict debug count
