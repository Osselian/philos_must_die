NAME = philo

SRCS = main.c \
	   init.c \
	   utils.c \
	   philo.c \
	   free_res.c \
	   init_data_set.c \
	   args_converter.c \
	   get_time_delta.c \
	   do_work.c \
	   check_availability.c

OBJ = $(SRCS:.c=.o) 

CFLAGS = -Wall -Werror -Wextra -g3 

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME) # -fsanitize=thread

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ) #$(BONUSOBJ)
	#make -C $(LIBFT) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
