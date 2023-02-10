NAME = ft_containers
CC = clang++
SEED = "42"

FLAGS = -Wall -Wextra -Werror

all:	main

main:
	@echo FT_CONTAINERS
	@echo seed: $(SEED)
	@$(CC) main_ft.cpp -o $(NAME) $(FLAGS) &&  ./$(NAME) $(SEED) > res_ft
	@cat res_ft
	@$(CC) main_std.cpp -o $(NAME) $(FLAGS) &&  ./$(NAME) $(SEED) > res_std
	@cat res_std

clean:
	@rm -rf $(NAME)
	@rm -f res_ft res_std

fclean: clean

re: clean all