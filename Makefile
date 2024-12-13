.PHONY: all clean fclean re

C_GREEN=\033[0;32m
C_RED=\033[0;31m
C_BLUE=\033[0;34m
C_CYAN=\033[0;36m
C_END=\033[0m

NAME = fdf

LIBFTPATH = source/libft

SPATH = source/
LIBXPATH = minilibx-linux

CC = cc
FLAG = -Wall -Wextra -Werror -I $(SPATH) -I $(LIBXPATH)
AR = ar rcs
RM = -rm -f

C_FILES = \
color_creation.c \
color_manipulation.c \
draw_pixels.c \
fdf.c \
key_events.c \
key_events_perspective.c \
parse_map.c \
render_frame.c \
vertice_rotations.c

HEADERS = \
fdf.h \
key_codes.h \
editable_macros.h

O_FILES_ROOT = $(C_FILES:.c=.o)

HEADERS := $(addprefix $(SPATH), $(HEADERS))
C_FILES := $(addprefix $(SPATH), $(C_FILES))

O_FILES_SOURCE = $(C_FILES:.c=.o)

all: $(NAME)

%.o: %.c $(HEADERS)
	if [ ! -d "$(LIBXPATH)" ]; then git clone https://github.com/42Paris/minilibx-linux.git $(LIBXPATH); fi
	$(CC) $(FLAG) -c $(C_FILES)
	$(RM) $(O_FILES_SOURCE)
	mv -f $(O_FILES_ROOT:$(SPATH)%=%) $(SPATH)

$(NAME): $(O_FILES_SOURCE)
	make -C $(LIBFTPATH)
	make -C $(LIBXPATH)
	$(CC) $(FLAG) $(O_FILES_SOURCE) -L $(LIBFTPATH) -l ft -L $(LIBXPATH) -l mlx_Linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(C_GREEN)⌘ $(NAME) compiled! ⌘$(C_END)"

clean:
	make -C $(LIBFTPATH) clean
	make -C $(LIBXPATH) clean
	$(RM) $(O_FILES_SOURCE)
	$(RM) $(O_BONUS_FILES)
	@echo "$(C_CYAN)⌘ $(NAME) cleaned up! ⌘$(C_END)"

fclean: clean
	make -C $(LIBFTPATH) fclean
	$(RM) $(NAME)
	$(RM) -r -f $(LIBXPATH)
	@echo "$(C_GREEN)⌘ $(NAME) removed! ⌘$(C_END)"

re: fclean all
