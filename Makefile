NAME = ft_containers

SRCS =	map_2-3_test.cpp

HDRS = vector.hpp utils.hpp vector_iterator.hpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -O3 -std=c++98

COMP = clang++

%.o: %.cpp		$(HDRS)
				@$(COMP) $(FLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(COMP) $(FLAGS) $(OBJS) -o $@

clean:
				@rm -f $(OBJS)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all


.PHONY:			all clean fclean re
