CC = cc #-fsanitize=thread -g
SRCS = philo/philo.c philo/philo_utils.c philo/ft_atoi.c philo/routine.c
SRCS_BONUS = phlo_bonus/philo_bonus.c phlo_bonus/ft_atoi.c phlo_bonus/philo_utils_bonus.c# #routine_bonus.c#
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME = philos
NAME_BONUS = philos_bonus

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