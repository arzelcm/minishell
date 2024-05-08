NAME = minishell

#----COLORS----#
DEF_COLOR = \033[0m
WHITE_BOLD = \033[1;39m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PINK = \033[1;35m
CYAN = \033[1;36m

#----COMPILER----#
CC = cc
CCFLAGS = -Wall -Werror -Wextra #-fsanitize=thread #-fsanitize=address

#----DIRS----#
BIN_DIR = bin/
INC_DIR = inc/
SRCS_DIR = src/
INCLUDES = -I$(INC_DIR)

#----LIBFT----#
LIBFT_DIR = lib/libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
INCLUDES += -I$(LIBFT_DIR)

#----READLINE----#
READLINE_DIR = lib/readline
READLINE_LIB = $(READLINE_DIR)/libreadline.a
LIBS += -L$(READLINE_DIR) -lreadline -lhistory -ltermcap
INCLUDES += -Ilib -I$(READLINE_DIR)

#----SHARED----#
SRCS =	
OBJS = $(SRCS:%.c=$(BIN_DIR)%.o)
DEPS = $(OBJS:%.o=%.d)

#----MANDATORY----#
MSRCS = minishell.c \
		custom_utils.c
MOBJS = $(MSRCS:%.c=$(BIN_DIR)%.o)
MDEPS = $(MOBJS:%.o=%.d)

#----BONUS----#
BSRCS = 
BDIR =	src/bonus
BOBJS = $(BSRCS:%.c=$(BIN_DIR)%.o)
BDEPS = $(BOBJS:%.o=%.d)

#----OS COMPATIBILITY----#
ifneq ($(OS),Windows_NT)
	UNAME_S = $(shell uname -s)
else
	UNAME_S = Windows
endif

#----MACROS----#
export GNL_BUFFER_SIZE := 50000

#----VPATH----#
vpath %.c $(SRCS_DIR):$(MDIR):$(BDIR):src/utils

#----LOG----#
LOG = log

#----RULES----#
all:
	@$(MAKE) --no-print-directory make_libft
	@$(MAKE) --no-print-directory $(NAME)

ifndef BONUS
$(NAME): $(READLINE_LIB) $(LIBFT_LIB) $(OBJS) $(MOBJS)
	@printf "$(BLUE)Linking objects and creating program...$(DEF_COLOR)\n"
	$(CC) $(CCFLAGS) $(OBJS) $(MOBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)$(NAME)$(GREEN) created!!!$(DEF_COLOR)"
else
$(NAME): $(LIBFT_LIB) $(OBJS) $(BOBJS)
	@printf "$(BLUE)Linking objects and creating bonus program...$(DEF_COLOR)\n"
	$(CC) $(CCFLAGS) $(OBJS) $(BOBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)$(NAME) Bonus$(GREEN) created!!!$(DEF_COLOR)"
endif

$(BIN_DIR)%.o: %.c Makefile
	@printf "$(CYAN)Compiling: $(PINK)$(notdir $<)...$(DEF_COLOR)\n"
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CCFLAGS) $(INCLUDES) -MMD -c $< -o $@

clean: libft_clean
	@rm -rf $(BIN_DIR)
	@echo "$(RED)bin/ deleted$(DEF_COLOR)"
	-$(MAKE) --no-print-directory -C $(READLINE_DIR) clean >>$(LOG) 2>&1

fclean: libft_fclean clean
	@rm -rf $(NAME) $(READLINE_DIR) log
	@echo "$(RED)Executable deleted$(DEF_COLOR)\n"

re: fclean all

bonus: 
	@$(MAKE) --no-print-directory BONUS=1

b: bonus

bonusre: fclean bonus

make_libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) bonus

libft_clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

libft_fclean:
	@echo "$(RED)Cleaning $(PINK)Libft$(RED)...$(DEF_COLOR)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

$(READLINE_LIB): $(READLINE_DIR)
	printf "$(BLUE)Compiling and linking library...$(DEF_COLOR)\n"
	$(MAKE) -s --no-print-directory -C $(READLINE_DIR) >>$(LOG) 2>&1
	printf "$(GREEN)\r\033[2K[✓] $(PINK)readline$(GREEN) created!!!$(DEF_COLOR)\n\n"

$(READLINE_DIR):
	printf "$(CYAN)Downloading: $(PINK)readline...$(DEF_COLOR)\n"
	cd lib; curl -s -O http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz
	rm -rf $(READLINE_DIR)
	mkdir -p $(READLINE_DIR)
	tar -xpf lib/readline-master.tar.gz -C $(READLINE_DIR) --strip-components 1
	rm -rf lib/readline-master.tar.gz
	printf "$(CYAN)Configuring: $(PINK)readline...$(DEF_COLOR)\n"
	cd $(READLINE_DIR); bash ./configure >>$(LOG) 2>&1

.PHONY: all \
		clean \
		fclean \
		re \
		bonus \
		bonusre \
		make_libft \
		libft_clean \
		libft_fclean \
		b \

-include $(DEPS)
-include $(MDEPS)
-include $(BDEPS)
.SILENT:
