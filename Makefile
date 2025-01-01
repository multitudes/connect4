
NAME 			= 	connect4

CC 				= 	cc

CFLAGS 		= 	-Wextra -Wall -Werror
CFLAGS 			+= 	-Iinclude -Isrc -O3 -Wunreachable-code -Ofast
# CFLAGS += -DDEBUG=1

# directories
OBJ_DIR			= 	obj/
SRC_DIR			= 	src/
LIBFTDIR 		= 	./lib/libft

LIBS 			+= 	$(LIBFTDIR)/libft.a

INCLUDES		=  	-I./include -I$(LIBMLX)/include -I$(LIBFTDIR)

SRCS 			= $(addprefix $(SRC_DIR), main.c checks.c utils.c players.c minimax.c)
OBJS 			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
HDRS 			= $(addprefix include/, connect.h checks.h utils.h players.h minimax.h)

LIBFT 			= $(LIBFTDIR)/libft.a
LIBFT_LIB 		= -Llibft -lft


# OS specific flags
UNAME 			= 	$(shell uname -s)
ifeq ($(UNAME), Linux)
	LIBS 		+=  -lbsd
else ifeq ($(UNAME), Darwin)

endif

all: $(LIBFT) $(NAME)

$(LIBFT):
	@if [ ! -d "lib/libft" ]; then \
	git clone https://github.com/multitudes/42-libft.git lib/libft; \
	fi
	$(MAKE) -C $(LIBFTDIR) all

# Static pattern rule for compilation - adding the .o files in the obj folder
# with includes for the libft that will allow the "libft.h" notation
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	# $(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@rm -rf $(NAME)
	# $(MAKE) -C $(LIBFTDIR) fclean


re: fclean all

.PHONY: all clean fclean re $(LIBFT)
