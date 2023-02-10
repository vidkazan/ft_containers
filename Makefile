NAME = ft_containers
CC = c++
SEED = "12345"

FLAGS = -Wall -Werror -Wextra

all:	main

vector_tests:	test_vector_capacity \
				test_vector_construction \
				test_vector_element_access \
				test_vector_iter_methods \
				test_vector_modifiers \
				test_vector_non_member_swap \
				test_vector_logical_operators

set_tests:		test_set_construction \
				test_set_iterators \
				test_set_capacity \
				test_set_lookup \
				test_set_modifiers \
				test_set_observers \
				test_set_logical_operators

stack_tests:		test_stack

main:
	@echo seed: $(SEED)
	@$(CC) main_ft.cpp -o $(NAME) $(FLAGS) &&  ./$(NAME) $(SEED) > res_ft
	@cat res_ft
	@$(CC) main_std.cpp -o $(NAME) $(FLAGS) &&  ./$(NAME) $(SEED) > res_std
	@cat res_std

clean:
	@rm -rf $(NAME)
	@rm -f res_ft res_std

fclean: clean

re: clean