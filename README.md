# minishell
Write a shell.

A shell is a program which executes commands from a string given by a prompt. 

<img width="226" alt="Screenshot 2024-07-08 at 16 17 56" src="https://github.com/arzelcm/minishell/assets/26092413/295d6b38-489f-4d43-b47e-1c496bcfe897">

## First steps

### The prompt
A prompt is the concept where your program waits for an input, in this case your prompt will have to wait for `STDIN` to have some `char *` input from the user on the terminal (a `tty`).

You can use your `get_next_line` and implement it to make it work as [The GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) or you can simply include this lib for Mac or use it for Linux.

#### How to include *The GNU Readline Library*
You could simply [download the readline-master.tar.gz](http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz), compile it and link it to your binary. But this is not the correct way to do it. Your project should only contain code made by your self not third-party code. Given that principle, we'll make our project download it, descompress it, compile it and link it as following.

```Makefile
$(READLINE_LIB): | $(READLINE_DIR)
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
```

### Signals

## Main actions
1. check syntax -> `lexer`
2. tokenize -> `tokenizer`
3. expanse args and redirections -> `expansor`
4. execute -> `executor`

## Testing
### Norme testing
```bash
norminette src inc lib/libft
```
### Some random test
```bash
make test
```
### Mpanic test
```bash
make mpanic
```
