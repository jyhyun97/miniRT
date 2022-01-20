NAME = miniRT
FLAGS = -Wall -Wextra -Werror# -fsanitize=address
SRCS_C = main.c\
		parsing/get_next_line.c\
		parsing/get_next_line_utils.c\
		parsing/util.c\
		parsing/set.c\
		parsing/split.c\
		parsing/create.c\
		parsing/check.c\
		rendering/render.c\
		rendering/vector.c\
		rendering/hit.c
SRCS = $(addprefix src/, $(SRCS_C))

OBJS = $(SRCS:.c=.o)
.c.o :
	gcc $(FLAGS) -c $< -o $@ -I include

$(NAME) : $(OBJS)
	@gcc $(FLAGS) -L./mlx -lmlx -framework OpenGL -framework Appkit $(OBJS) -o $(NAME)
all : $(NAME)

clean :
	rm -rf $(OBJS)
fclean :	clean
	rm -rf $(NAME)
re :	fclean all

.PHONY : all clean fclean re