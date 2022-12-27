# //= Variables =//

NAME	= fdf
CFLAGS	= -w -Wunreachable-code -Wall -Werror -Wextra -g
LIBMLX	= MLX_42
LIBFT	= libft

INCLUDES = includes/fdf.h  
HEADERS	= -I ./includes -I $(LIBMLX)/include -I $(LIBFT)
LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a ./$(LIBFT)/libft.a
MANDA_SRC := draw.c fdf.c get_next_line_utils.c get_next_line.c init.c parsing.c utils.c 
MANDA_DIR	:=	sources/
SRC	:= $(addprefix $(MANDA_DIR), $(MANDA_SRC))
OBJS	= ${SRC:.c=.o}
LIB :=	libft/libft.a MLX_42/libmlx42.a

BOLD	:= \1\33[1m\2
BLACK	:= \1\33[30;1m\2
RED		:= \1\33[31;1m\2
GREEN	:= \1\33[32;1m\2
YELLOW	:= \1\33[33;1m\2
BLUE	:= \1\33[34;1m\2
MAGENTA	:= \1\33[35;1m\2
CYAN	:= \1\33[36;1m\2
WHITE	:= \1\33[37;1m\2
RESET	:= \1\33[0m\2\3

# //= Recipes =//

all: lib libmlx $(NAME) 

# $(LIBMLX):
# 	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

# $(LIBFT): 
# 	git clone https://github.com/GuzzyWasTaken/libft.git $(LIBFT)

lib: $(LIBFT)
	@$(MAKE) -C $(LIBFT)

libmlx: $(LIBMLX)
	@$(MAKE) -C $(LIBMLX)


%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -o $@ -c $< && printf "$(GREEN)\rCompiling: $(notdir $<)\r\33[33C[OK]\n$(RESET)"

$(NAME): $(OBJS) $(INCLUDES) Makefile
	@$(CC) $(CFLAGS) $(LIB) $(LIBS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C  $(LIBFT) 
	@$(MAKE) clean -C $(LIBMLX)

fclean:
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT)
	@$(MAKE) fclean -C $(LIBMLX)


re: fclean all

.PHONY: all, clean, fclean, re, libmlx, lib