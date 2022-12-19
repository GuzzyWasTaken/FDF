# //= Variables =//

NAME	= fdf
CFLAGS	= -w -Wunreachable-code -Wall -Werror -Wextra -g
LDFLAGS = -fsanitize=address -g
LIBMLX	= MLX_42
LIBFT	= libft
USER	= auzochuk

INCLUDES = includes/fdf.h  
HEADERS	= -I ./includes -I $(LIBMLX)/include -I $(LIBFT)
LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a ./$(LIBFT)/libft.a
MANDA_SRC := draw.c fdf.c get_next_line_utils.c get_next_line.c init.c parsing.c utils.c 
MANDA_DIR	:=	sources/
SRC	:= $(addprefix $(MANDA_DIR), $(MANDA_SRC))
OBJS	= ${SRCS:.c=.o}

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \33[32;1m
YELLOW	:= \33[33;1m
BLUE	:= \33[34;1m
MAGENTA	:= \33[35;1m
CYAN	:= \33[36;1m
WHITE	:= \33[37;1m
RESET	:= \33[0m

# //= Recipes =//

all: lib libmlx $(NAME) 

$(LIBMLX):
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

$(LIBFT):
	git clone https://github.com/GuzzyWasTaken/libft.git $(LIBFT)

lib: $(LIBFT)
	@$(MAKE) -C $(LIBFT)

libmlx: $(LIBMLX)
	@$(MAKE) -C $(LIBMLX)


%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -o $@ -c $< && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(SRC) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBS) $(SRC) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, lib