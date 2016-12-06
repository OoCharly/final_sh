.PHONY: fclean re
.SUFFIXES:
NAME = 21sh
FLAGS = -Wall -Wextra -Werror
FLAGSPOSIX = -ansi -pedantic -D_POSIX_SOURCE=1
SRCS = $(foreach S, $(SRC), srcs/$(S))
OBJ = $(SRCS:.c=.o)
TERMCAPS = -lm -lncurses
HEAD = -I libft/includes -I includes
OS = $(shell uname -s)
SRC = \
autocomp/auto_utils.c \
autocomp/autocomp.c \
autocomp/buildlist.c \
autocomp/command.c \
autocomp/getenv.c \
autocomp/move.c \
autocomp/print.c \
autocomp/rep.c \
autocomp/support.c \
builtins/builtin.c \
builtins/cd.c \
builtins/echo.c \
builtins/env.c \
builtins/environ.c \
builtins/jobs.c \
builtins/jobs_utils.c \
core/cmp.c \
core/errors.c \
core/free.c \
core/free_list.c \
core/free_pros.c \
core/hash.c \
core/main.c \
core/minishell.c \
core/qerror.c \
core/signal.c \
globbing/globbing.c \
globbing/match.c \
history/history.c \
history/history_backup.c \
history/history_search_down.c \
history/history_search_up.c \
history/scanchr.c \
history/searchengine.c \
history/sprompt.c \
run_command/build_sentence.c \
run_command/env_var_replace.c \
run_command/exec.c \
run_command/files.c \
run_command/globbing_replace.c \
run_command/heredoc.c \
run_command/lexer.c \
run_command/lexer_av.c \
run_command/lexer_match_op.c \
run_command/lexer_sshell.c \
run_command/parser.c \
run_command/parser_multiple_fd.c \
run_command/parser_sequence.c \
run_command/pipehandle.c \
run_command/quote_replace.c \
run_command/wait.c \
scan_input/arrowlr.c \
scan_input/arrowud.c \
scan_input/checknewline.c \
scan_input/chrparse.c \
scan_input/cursor.c \
scan_input/deletion.c \
scan_input/prompt.c \
scan_input/quotecheck.c \
scan_input/streamscan.c \
scan_input/syntax_color.c \
scan_input/termcaps.c \
scan_input/underline_mess.c \
scan_input/winsize.c \

ifeq ($(OS), Linux)
	FLAGS += -D LINUX
endif

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(HEAD) $^ -L libft -l ft -o $@ $(TERMCAPS)

%.o: %.c libft/libft.a
	gcc $(FLAGS) $(HEAD) -c $< -o $@

lib:
	make -C libft

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

re: fclean lib $(DNAME)
