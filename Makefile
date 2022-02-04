NAME = miniRT
FLAGS = -Wall -Wextra -Werror# -fsanitize=address
SRCS_C = main.c\
		parsing/check.c\
		parsing/create.c\
		parsing/get_next_line_utils.c\
		parsing/get_next_line.c\
		parsing/info.c\
		parsing/phong.c\
		parsing/set_object.c\
		parsing/set.c\
		parsing/split.c\
		parsing/util.c\
		rendering/hit.c\
		rendering/mlx_util.c\
		rendering/render.c\
		rendering/vector1.c\
		rendering/vector2.c\
		print.c
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