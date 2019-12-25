NAME = miniRT

GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS = minirt.c utils/*.c ft_atof.c parser/*.c \
	objects/*.c object_printer/obj_printer.c  vector_math/vector_math.c \
	rays_and_intersections/ray_intersections.c menu/menu.c lighting.c \
	raytracing.c raytracing_utils.c save_bmp/bmp.c events_one.c events_two.c events_three.c

all: $(NAME)

$(NAME): 
	make -C ft_printf/ re
	gcc $(SRCS) $(GNL_SRCS) -DBUFFER_SIZE=80 -Lft_printf -lftprintf -o $(NAME) -g -L../mlx -lmlx -framework OpenGL -framework Appkit -O3 #-fsanitize=address  #-Wframe-larger-than=1024

clean: 
	make -C ft_printf/ clean

fclean: clean
	rm -rf miniRT

re: fclean all

c : re
	clear
	./$(NAME) asdf.rt
