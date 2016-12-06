/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:23:28 by tboos             #+#    #+#             */
/*   Updated: 2016/11/23 17:05:08 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "posix.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>
# include <dirent.h>
# include <stdio.h>
# include <termios.h>
# include <fcntl.h>
# include <signal.h>
# include <pwd.h>
# include "libft.h"
# include "core.h"
# include "scan_input.h"
# include "autocomp.h"
# include "run_command.h"
# include "error.h"

# ifdef LINUX
#  include "keys_linux.h"
# else
#  include "keys_mac.h"
# endif

#endif
