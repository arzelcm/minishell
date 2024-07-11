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
CCFLAGS = -Wall -Werror -Wextra -O3 #-g -fsanitize=address

#----OS COMPATIBILITY----#
ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CCFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CCFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CCFLAGS += -D IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CCFLAGS += -D LINUX
		export LINUX=1
    endif
    ifeq ($(UNAME_S),Darwin)
        CCFLAGS += -D OSX
		export DARWIN=1
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CCFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CCFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CCFLAGS += -D ARM
    endif
endif

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
ifndef LINUX
READLINE_LIB = $(READLINE_DIR)/libreadline.a
LIBS += -L$(READLINE_DIR)
endif
LIBS += -lreadline -lhistory -ltermcap
INCLUDES += -Ilib -I$(READLINE_DIR)

#----SHARED----#
SRCS =	
OBJS = $(SRCS:%.c=$(BIN_DIR)%.o)
DEPS = $(OBJS:%.o=%.d)

#----MANDATORY----#
MSRCS = minishell.c \
		lexer.c \
		lexer_utils.c \
		utils.c \
		expansor.c \
		executor.c \
		open.c \
		open_utils.c \
		execute_command.c \
		execute_command_utils.c \
		executor_utils.c \
		pdata_helpers.c \
		signals.c \
		safe_utils.c \
		expansor_vars.c \
		tokenizer.c \
		quotes_utils.c \
		tokenizer_utils.c \
		tokenizer_redirections.c \
		token.c \
		environment.c \
		environment_helper.c \
		pwd.c \
		env.c \
		echo.c \
		exit.c \
		export.c \
		export_utils.c \
		utils_builtins.c \
		unset.c \
		cd.c \
		safe_libft.c \
		words.c
MOBJS = $(MSRCS:%.c=$(BIN_DIR)%.o)
MDEPS = $(MOBJS:%.o=%.d)

#----BONUS----#
BSRCS = 
BDIR =	src/bonus
BOBJS = $(BSRCS:%.c=$(BIN_DIR)%.o)
BDEPS = $(BOBJS:%.o=%.d)

#----MACROS----#
export GNL_BUFFER_SIZE := 50000

#----VPATH----#
vpath %.c $(SRCS_DIR):$(MDIR):$(BDIR):src/utils:src/expansor:src/lexer:src/tokenizer:src/executor:src/executor/builtins:src/environment

#----LOG----#
LOG = log

#----TEST----#
TESTROOT = 42_minishell_tester
TESTDIR = ./$(TESTROOT)-master
TESTREPO = $(HOME)/$(TESTROOT)

TEST_INSTALL = $(TESTDIR)/install.sh
TEST_INSTALL_TMP = $(TESTDIR)/install_tmp.sh
TESTER = $(TESTDIR)/tester.sh
START_TEST = $(TESTER) m

ifdef FORCE_PROMPT
DEFINES += -DFORCE_PROMPT=1
endif




#----- R U L E S -----#



all:
	@$(MAKE) --no-print-directory make_libft
	@$(MAKE) --no-print-directory $(NAME)

ifndef BONUS
$(NAME): $(READLINE_LIB) $(LIBFT_LIB) $(OBJS) $(MOBJS)
	@printf "$(BLUE)Linking objects and creating program...$(DEF_COLOR)\n"
	$(CC) $(CCFLAGS) $(DEFINES) $(OBJS) $(MOBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)$(NAME)$(GREEN) created!!!$(DEF_COLOR)"
else
$(NAME): $(LIBFT_LIB) $(OBJS) $(BOBJS)
	@printf "$(BLUE)Linking objects and creating bonus program...$(DEF_COLOR)\n"
	$(CC) $(CCFLAGS) $(DEFINES) $(OBJS) $(BOBJS) $(LIBFT_LIB) $(LIBS) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)$(NAME) Bonus$(GREEN) created!!!$(DEF_COLOR)"
endif

$(BIN_DIR)%.o: %.c Makefile
	@printf "$(CYAN)Compiling: $(PINK)$(notdir $<)...$(DEF_COLOR)\n"
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CCFLAGS) $(DEFINES) $(INCLUDES) -MMD -c $< -o $@

clean: libft_clean test_clean
	@rm -rf $(BIN_DIR)
	@echo "$(RED)bin/ deleted$(DEF_COLOR)"

fclean: libft_fclean readline_clean clean
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

readline_clean:
	-$(MAKE) --no-print-directory -C $(READLINE_DIR) clean >>$(LOG) 2>&1

$(READLINE_LIB): | $(READLINE_DIR)
ifndef LINUX
	printf "$(BLUE)Compiling and linking library...$(DEF_COLOR)\n"
	$(MAKE) -s --no-print-directory -C $(READLINE_DIR) >>$(LOG) 2>&1
	printf "$(GREEN)\r\033[2K[✓] $(PINK)readline$(GREEN) created!!!$(DEF_COLOR)\n\n"
else
	$(MAKE) --no-print-directory readline_clean
endif

$(READLINE_DIR):
ifndef Linux
	printf "$(CYAN)Downloading: $(PINK)readline...$(DEF_COLOR)\n"
	cd lib; curl -s -O http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz
	rm -rf $(READLINE_DIR)
	mkdir -p $(READLINE_DIR)
	tar -xpf lib/readline-master.tar.gz -C $(READLINE_DIR) --strip-components 1
	rm -rf lib/readline-master.tar.gz
	printf "$(CYAN)Configuring: $(PINK)readline...$(DEF_COLOR)\n"
	cd $(READLINE_DIR); bash ./configure >>$(LOG) 2>&1
endif

test_clean:
	@rm -rf	$(TESTDIR) $(TESTREPO)
	rm -rf mpanic-main

test:
	bash --version
ifdef FORCE_PROMPT
	$(MAKE) --no-print-directory clean all
endif
	curl -sLO https://github.com/zstenger93/42_minishell_tester/archive/refs/heads/master.zip
	unzip master.zip > /dev/null
	rm -rf master.zip
	head -n 33 $(TEST_INSTALL) > $(TEST_INSTALL_TMP)
	rm -rf $(TEST_INSTALL)
	mv $(TESTDIR)/install_tmp.sh $(TEST_INSTALL) 
	chmod 744 $(TEST_INSTALL)
	$(TEST_INSTALL)
	echo "[[ \$$1 != \"-f\" ]] && rm -f \"\\\$$HOME\" \"\\\$$USER\" \"\\\$$USER'\\\$$USER'\"" >> $(TESTER)
	$(START_TEST)

mpanic:
ifndef FORCE_PROMPT
	$(MAKE) --no-print-directory FORCE_PROMPT=1 clean all
endif
	curl -sLO https://github.com/ChewyToast/mpanic/archive/refs/heads/main.zip
	unzip main.zip > /dev/null
	rm -rf main.zip
	cd mpanic-main; bash mpanic.sh;
	cd mpanic-main; bash mpanic.sh

install_bash:
	curl -LO https://ftp.gnu.org/gnu/bash/bash-3.2.57.tar.gz
	tar -xpf bash-3.2.57.tar.gz;
	cd bash-3.2.57; ./configure --build=aarch64-unknown-linux-gnu; make; make install;
	rm -rf bash-3.2.57.tar.gz bash-3.2.57

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
		test \
		panic \
		test_clean
		install_bash

-include $(DEPS)
-include $(MDEPS)
-include $(BDEPS)
.SILENT:
