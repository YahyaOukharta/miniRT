NAME = miniRT

GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c

FLAGS = -Wall -Werror -Wextra

SRCS = minirt.c utils/*.c parser/*.c \
	objects/*.c   vector_math/*.c \
	rays_and_intersections/inter_*.c menu/*.c lighting.c \
	raytracing.c raytracing_utils.c save_bmp/bmp.c events_one.c events_two.c events_three.c \

all: $(NAME)

$(NAME): 
	make -C ft_printf/ re
	gcc $(FLAGS) $(SRCS) $(GNL_SRCS) -DBUFFER_SIZE=80 -Lft_printf -lftprintf -o $(NAME) -g \
		-L../mlx -lmlx -framework OpenGL -framework Appkit -O3 \
		#-fsanitize=address  #-Wframe-larger-than=1024
clean: 
	make -C ft_printf/ clean

fclean: clean
	rm -rf miniRT

re: fclean all

c : re
	clear
	./$(NAME) asdf.rt

n :
	norminette $(SRCS) 

