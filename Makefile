# name of executable
NAME=philo

# list of folders where C files are stored
# can NOT BE same folder as Makefile like:"." must be subfolder
CODEDIRS=philosof
#lexer sources parser expander builtin

# list of directories that could have includes in it. meaning .h files
INCDIRS=header
# folder where O-Files and Dependency files will be created in
OBJDIR=objects

# compiler
CC=cc

# list of optimization flags
OPT=#-O0

# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD

# flags that are specific to this project
EXTRAFLAGS=-pthread

# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -Werror -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))

# regular expression replacement
OBJECTS=$(patsubst %.c,$(OBJDIR)/%.o,$(CFILES))
DEPFILES=$(patsubst %.c,$(OBJDIR)/%.d,$(CFILES))

# COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_CYAN=\033[1;33m
COLOR_MAGENTA=\033[1;35m
COLOR_END=\033[0m
COLOR_B_MAGENTA=\033[1;35m
BG_CYAN=\033[48;5;250m

BG_BLACK=\033[40m

# RULES BEGIN HERE
.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	@echo " ]"
	@printf "  $(COLOR_MAGENTA)$(NAME)$(COLOR_END) executable:\t\t\t"
	@$(CC) -o $@ $(OBJECTS) $(EXTRAFLAGS)
	@echo "[$(COLOR_GREEN) done $(COLOR_END)]"

# only want the .c file dependency here, thus $< instead of $^.
$(OBJDIR)/%.o:%.c msg
	@printf "$(COLOR_GREEN)+$(COLOR_END)"
	@mkdir -p $(foreach D,$(CODEDIRS), $(OBJDIR)/$(D))
	@$(CC) $(CFLAGS) -c -o $@ $<

# this .INTERMEDIATE step prints out the msg only once when compiling all the .o files
.INTERMEDIATE: msg
msg:
	@printf "  compiling $(NAME) object files:\t[ "

# removes the object directory in the root directory of project
# starts the libft clean Makefile rule. 
clean:
	@echo "  $(NAME) objects and dependencies\t[ $(COLOR_RED)-$(COLOR_END) ]"
	@rm -rf $(OBJDIR)

# removes executable in root folder of project
# starts libft execlean rule which only removes the libft.a file because the rest is cleaned 
# by the libft clean rule that libft fclean calls.
fclean: clean
	@echo "  executable $(NAME)\t\t\t[ $(COLOR_RED)-$(COLOR_END) ]"
	@rm -rf $(NAME)

# fclean and then all
re: fclean all

# shell commands are a set of keystrokes away
distribute: clean
	tar zcvf dist.tgz *

# @ silences the printing of the command
# $(info ...) prints output
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES)

# add .PHONY so that the non-targetfile - rules work even if a file with the same name exists.
.PHONY: all clean fclean re distribute diff test t val
