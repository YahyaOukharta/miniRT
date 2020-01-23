NAME = miniRT

GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c

FT_PRINTF_PATH = ./ft_printf/

MLX_PATH = ./mlx/

FLAGS = -Wall -Werror -Wextra

SRCS = minirt.c utils/colors.c utils/parser_utils.c utils/string_array.c utils/utils.c \
	parser/check_amb_light.c parser/check_light.c parser/check_sphere.c parser/parser.c \
	parser/check_cam.c parser/check_plane.c parser/check_square.c parser/parser_utils.c \
	parser/check_cylinder.c parser/check_res.c parser/check_triangle.c \
	objects/camera.c objects/light.c objects/plane.c objects/square.c \
	objects/cylinder.c objects/objects.c objects/sphere.c objects/triangle.c \
	vector_math/vec_math_rot.c vector_math/vector_math_one.c vector_math/vector_math_two.c \
	rays_and_intersections/inter_cylinder.c rays_and_intersections/inter_sphere.c \
	rays_and_intersections/inter_triangle.c rays_and_intersections/inter_plane.c \
	rays_and_intersections/inter_square.c \
	menu/get_obj_details.c menu/get_obj_details_two.c menu/menu.c menu/menu_two.c \
	lighting.c raytracing.c raytracing_utils.c \
	save_bmp/bmp.c \
	events_one.c events_two.c events_three.c \
	skybox.c \

all: $(NAME)

$(NAME): 
	make -C $(MLX_PATH)
	make -C $(FT_PRINTF_PATH)

	gcc $(FLAGS) $(SRCS) $(GNL_SRCS) \
		-DBUFFER_SIZE=80 \
		-L$(FT_PRINTF_PATH) -lftprintf \
		-L$(MLX_PATH) -lmlx -framework OpenGL -framework Appkit \
		-O3 -o $(NAME) -g
clean:
	make -C ft_printf/ clean

fclean: clean
	make -C $(MLX_PATH) clean
	make -C $(FT_PRINTF_PATH) fclean
	rm -rf $(NAME) 
	rm -rf $(NAME).dSYM

re: fclean all

c : re
	clear
	./$(NAME) scenes/objects.rt

n : fclean
	norminette $(FT_PRINTF_PATH) utils/ vector_math/ scenes/ parser/ objects/ menu/ *.c *.h
