NAME = minishell

AUTHOR          = "Daniel Herszenhaut <dherszen@student.42.rio> and Matheus C M El Honais Silva <mc-m-el-@student.42.rio>"

RED				= \033[0;31m
BLUE			= \033[0;34m
GREEN			= \033[0;32m
NO_COLOR		= \033[0m

# Mandatory files and paths
H_SRCS          = ./includes
SRCS_PATH       = srcs
OBJS_PATH       = ./objs
BUILTINS_PATH   = ${SRCS_PATH}/builtins
ENV_PATH        = ${SRCS_PATH}/env
ERRORS_VAL_PATH = ${SRCS_PATH}/errors_validation
EXEC_PATH       = ${SRCS_PATH}/exec
HEREDOC_PATH    = ${SRCS_PATH}/heredoc
PARSER_PATH     = ${SRCS_PATH}/parser
RDIR_PATH       = ${SRCS_PATH}/redirects
VAR_EXP_PATH    = ${SRCS_PATH}/var_exp
C_SRCS 			= ${BUILTINS_PATH}/builtins_1.c \
				  ${BUILTINS_PATH}/builtins_2.c \
				  ${BUILTINS_PATH}/builtins_3.c \
				  ${BUILTINS_PATH}/builtins_utils_1.c \
				  ${ENV_PATH}/env_utils_1.c \
				  ${ENV_PATH}/env_utils_2.c \
				  ${ENV_PATH}/env_utils_3.c \
				  ${ENV_PATH}/env_utils_4.c \
				  ${ENV_PATH}/env_utils_5.c \
				  ${ERRORS_VAL_PATH}/errors_validation_1.c \
				  ${ERRORS_VAL_PATH}/errors_validation_2.c \
				  ${ERRORS_VAL_PATH}/errors_validation_3.c \
				  ${EXEC_PATH}/exec_1.c \
				  ${EXEC_PATH}/exec_2.c \
				  ${EXEC_PATH}/exec_utils_1.c \
				  ${EXEC_PATH}/exec_utils_2.c \
				  ${EXEC_PATH}/exec_utils_3.c \
				  ${SRCS_PATH}/main.c \
				  ${PARSER_PATH}/parser_1.c \
				  ${PARSER_PATH}/parser_2.c \
				  ${PARSER_PATH}/parser_3.c \
				  ${PARSER_PATH}/parser_utils_1.c \
				  ${PARSER_PATH}/parser_utils_2.c \
				  ${PARSER_PATH}/parser_utils_3.c \
				  ${SRCS_PATH}/signal_handler.c  \
				  ${VAR_EXP_PATH}/var_exp_1.c \
				  ${VAR_EXP_PATH}/var_exp_utils_1.c \
				  ${VAR_EXP_PATH}/var_exp_utils_2.c \
				  ${VAR_EXP_PATH}/var_exp_utils_3.c \
				  ${HEREDOC_PATH}/heredoc_1.c \
				  ${HEREDOC_PATH}/heredoc_2.c \
				  ${RDIR_PATH}/redirects_1.c \
				  ${RDIR_PATH}/redirects_2.c

C_OBJS		   = ${addprefix ${OBJS_PATH}/, ${C_SRCS:.c=.o}}

# libft
LIBFT_PATH      = ./libft
LIBFT           = ${LIBFT_PATH}/libft.a

# Remove files
RM              = rm -f

# compiler and compiler flags
CC              = cc
C_FLAGS        ?= -Wall   \
                  -Wextra \
                  -Werror \
                  -ggdb3
#				   -fsanitize=address -fsanitize=undefined

RL_FLAGS = -lreadline \

OS := $(shell uname)
ifeq ($(OS), Darwin)

C_FLAGS += -I$(shell brew --prefix readline)/include
RL_FLAGS += -L$(shell brew --prefix readline)/lib
endif

# Default c.o. rule
${OBJS_PATH}/%.o: %.c
				@mkdir -p $(@D)
				@${CC} ${C_FLAGS} -c $< -o $@ -I${H_SRCS}

all:			${NAME}

${NAME}:		${LIBFT} ${C_OBJS}
				@${CC} ${C_FLAGS} ${C_OBJS} -o ${NAME} -I${H_SRCS} ${LIBFT} ${RL_FLAGS} && echo "✅ ${BLUE}${NAME}${GREEN} has been compiled!${NO_COLOR}" || echo "❌ ${BLUE}${NAME}${RED} failed to compile${NO_COLOR}"

# Rule for building libft
libft:			${LIBFT}

${LIBFT}:
				@make -C ${LIBFT_PATH} all > /dev/null && echo "✅ ${BLUE}Libft ${GREEN}compilation successful!${NO_COLOR}" || echo "❌ ${RED}Libft compilation failed!${NO_COLOR}"

# Clean targets
clean:
	@make -C ${LIBFT_PATH} fclean > /dev/null && echo "✅ ${BLUE}Libft ${GREEN}files successful deleted!${NO_COLOR}" || echo "❌ ${RED}Libft files deleting failed!${NO_COLOR}"
	@${RM} -rf ${OBJS_PATH} && echo "✅ ${GREEN}All ${BLUE}${NAME} ${GREEN}objects erased!${NO_COLOR}" || echo "❌ ${RED}All ${BLUE}${NAME} ${RED} objects erasing failed!${NO_COLOR}"

fclean: clean
	@${RM} ${NAME} && echo "✅ ${BLUE}${NAME} ${GREEN}binaries erased!${NO_COLOR}" || echo "❌ ${BLUE}${NAME} ${RED}binaries erasing failed!${NO_COLOR}"

re: fclean all

valgrind: $(NAME)
			valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=./rl.supp ./$(NAME)

.PHONY: all clean fclean re
