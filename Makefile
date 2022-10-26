NAME = philo
NAME_SAN = philo_data_race_check
all: $(NAME)
$(NAME):
	gcc -Wall -Werror -Wextra main.c struct.c utils.c threads.c leaks_checker/libleaks.a -o $(NAME)
clean:
	rm -f *.o
fclean:	clean
	rm -f $(NAME)
clean_san:
	rm -f $(NAME_SAN)
san: $(NAME_SAN)
$(NAME_SAN):
	gcc -Wall -Werror -Wextra main.c struct.c utils.c threads.c -fsanitize=thread -o $(NAME_SAN)
re:	fclean all