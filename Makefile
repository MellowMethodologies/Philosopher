CC = cc
SRCS = philo.c philo_utils.c ft_atoi.c routine.c
SRCS_BONUS = philo_bonus.c ft_atoi.c# philo_utils_bonus.c# #routine_bonus.c#
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME = philo
NAME_BONUS = philo_bonus

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean all re bonus