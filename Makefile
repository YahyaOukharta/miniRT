NAME = miniRT

GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c

SRCS = minirt.c utils/utils.c ft_atof.c file_checker/file_checker.c \
	objects/objects.c object_printer/obj_printer.c

all: $(NAME)

$(NAME): 
	make -C ft_printf/ re
	gcc $(SRCS) $(GNL_SRCS) -DBUFFER_SIZE=80 -Lft_printf -lftprintf -o $(NAME) -g

clean: 
	make -C ft_printf/ clean

fclean: clean
	rm -rf miniRT

re: fclean all

c : re
	clear
	./$(NAME) asdf.rt
