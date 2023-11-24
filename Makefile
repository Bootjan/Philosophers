MAIN = main2.c

SRCS = $(MAIN)

OBJS = ${SRCS:%.c=${OBJS_DIR}/%.o}
NAME = philo
VPATH = .

I_DIRS := $(shell find . -type f -name "*.h" -exec dirname {} + | uniq)
INCLUDE = ${I_DIRS:%=-I%}

CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJS_DIR = ./objs

RM = rm -f

all:	${NAME}

${NAME}: ${OBJS_DIR} ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "./philo made!"

${OBJS_DIR}:
	@mkdir -p ${OBJS_DIR}
	@echo "./objs made!"

${OBJS_DIR}/%.o:	%.c
	@${CC} ${CFLAGS} -c $< -o $@ ${INCLUDE}

clean:	
	@${RM} -r ${OBJS_DIR}
	@echo "Philo objects removed!"

fclean: clean
	@${RM} ${NAME}
	@echo "./philo removed!"
	@rm -rf ${OBJS_DIR}
	@echo "./objs removed!"

re: fclean all

.PHONY: all clean re clean fclear
