NAME = cub3D

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRC = gnl/get_next_line.c gnl/get_next_line_utils.c \
    parsing/parsing.c parsing/check_file_ext.c parsing/parse_map_file.c \
    parsing/parsing_utils.c parsing/parse_map_file1.c parsing/parse_map_file2.c \
    parsing/parse_map_file3.c parsing/clean.c parsing/ft_split.c

HEADER = cub3d.h

MXFLAGS = -lmlx -framework OpenGL -framework AppKit

OSRC = $(SRC:%.c=%.o)

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) -c $< $(CFLAGS) -o $@
	@echo "Compiling" $< "to" $@

$(NAME) : $(OSRC)
	$(CC) $(CFLAGS) $(MXFLAGS) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all