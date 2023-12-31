MAIN = main.c
FILES = handling_args.c utils.c life_of_philo.c thread_utils.c stop_threads.c have_diner.c

SRCS = $(MAIN)\
$(FILES)

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
NAME = philo
VPATH = .

I_DIRS := $(shell find . -type f -name "*.h" -exec dirname {} + | uniq)
INCLUDE = $(I_DIRS:%=-I%)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address -g
OBJS_DIR = ./objs

RM = rm -f

all:	$(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) made!"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "./objs made!"

$(OBJS_DIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:	
	@$(RM) -r $(OBJS_DIR)
	@echo "$(NAME) objects removed!"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) removed!"
	@rm -rf $(OBJS_DIR)
	@echo "./objs removed!"

re: fclean all

.PHONY: all clean re clean fclear

