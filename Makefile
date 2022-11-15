NAME			=	philo

SRCDIR 			=	./

SRC				=   utils.c\
					main.c\
					struct.c\
					threads.c\

SRCS			=	$(addprefix $(SRCDIR), $(SRC))

OBJS			=	$(SRCS:.c=.o)

CC			= gcc

CFLAGS 		= -Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(SRCS) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJS) $(OBJSBONUS)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

NAME_SAN = philo_data_race_check

san: $(NAME_SAN)

$(NAME_SAN):
	@gcc -Wall -Werror -Wextra main.c struct.c utils.c threads.c -fsanitize=thread -o $(NAME_SAN)