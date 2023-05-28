CC = cc
SRCS = philo.c philo_utils.c ft_atoi.c routine.c
SRCS_BONUS = philo_bonus.c ft_atoi.c# philo_utils_bonus.c# #routine_bonus.c#
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME = philo
NAME_BONUS = philo_bonus

all: $(NAME)

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re