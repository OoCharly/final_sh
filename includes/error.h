/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:23:05 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:23:08 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define CR_ERROR 1
# define FCR_ERROR 2
# define SERROR 4
# define EEXIT 8
# define PATH_MAX_ERR "path too long to get pwd"
# define PATH_MAX_EXEED "path too long"
# define SAVE_H_ERR "wasn't abble to save history"
# define LOAD_H_ERR "wasn't abble to load history, backup file is missing"
# define JEDI_ERR "i couldn't kill my father, he's a jedi"
# define BEAWARE_ERR "be aware display problem may occur"
# define ANSI_USE "unable to get terminal, default ansi code will be use"
# define TERM_ERR "fail to set terminal, problems may occur"
# define RESET_TERM_ERR "fail to reset terminal, so sorry i couldn't !"
# define SCAN_ERR "error while scanning command"
# define HEREDOC_ERR "heredoc delimiter is eof instead of"
# define PARSE_ERR "parse error near"

/*
** quotes errors
*/
# define QUOTE_ERR "please end your quote before running command"
# define PAR_ERR "missing '(' ')' '[' ']' '{' '}' or \"`\" character"
# define BACK_ERR "missing character after backslash"

/*
** signals errors
*/
# define ERR_HUP "Hangup detected on controlling terminal"
# define ERR_INT "Got killed by keyboard"
# define ERR_QUIT "Quit from keyboard"
# define ERR_ILL "Illegal Instruction"
# define ERR_TRAP "Trace/breakpoint trap"
# define ERR_ABRT "Abort signal from abort(3)"
# define ERR_BUS "Bus error (bad memory access)"
# define ERR_FPE "Floating point exception"
# define ERR_KILL "got killed by a signal"
# define ERR_USR1 "User-defined signal 1"
# define ERR_USR2 "User-defined signal 2"
# define ERR_SEGV "Segmentation fault"
# define ERR_PIPE "Broken pipe: write to pipe with no readers"
# define ERR_ALRM "timer signal from alarm(2)"
# define ERR_TERM "Termination signal"
# define ERR_STKFLT "Stack fault on coprocessor"
# define ERR_CHLD "Child stopped or terminated"
# define ERR_CONT "Process continuing"
# define ERR_STOP "Stop process"
# define ERR_TSTP "Pause process"
# define ERR_TTIN "Terminal input for background process"
# define ERR_TTOU "Terminal output for background process"
# define ERR_URG "Urgent condition on socket"
# define ERR_XCPU "CPU time limit exceeded"
# define ERR_XFSZ "File size limit exceeded"
# define ERR_VTALRM "Virtual alarm clock"
# define ERR_PROF "Profiling timer expired"
# define ERR_WINCH "Windows got resized"
# define ERR_POLL "Pollable event"
# define ERR_PWR "Power failure"
# define ERR_SYS "Invalid argument to routine"

#endif
