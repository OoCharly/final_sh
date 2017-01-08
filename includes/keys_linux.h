/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_linux.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:51:46 by tboos             #+#    #+#             */
/*   Updated: 2017/01/08 18:09:15 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_LINUX_H
# define KEYS_LINUX_H

# define SYSTEM 0
# define MAC 1
# define LINUX 0
/*
** CLF		\n
** SUP		suprr
** CHT		\t
** DEL		del
** LEF		left
** RIG		right
** UPP		up
** DOW		down
** CLEF		ctrl + left
** CRIG		ctrl + right
** CUPP		ctrl + up
** CDOW		ctrl + down
** CRS		ctrl + R
** END		end
** HOM		home
** NUL		\0
** ESC		escape
** CTRLD	ctrl + D
*/

# define CLF	0x0A
# define SUP	0x7E335B1B
# define CHT	0x09
# define DEL	0x7F
# define LEF	0x445B1B
# define RIG	0x435B1B
# define UPP	0x415B1B
# define DOW	0x425B1B
# define CLEF	0x44353B315B1B
# define CRIG	0x43353B315B1B
# define CUPP	0x41353B315B1B
# define CDOW	0x42353B315B1B
# define CRS	0x12
# define END	0x464F1B
# define HOM	0x484F1B
# define NUL	0x00
# define ESC	0x1b
# define CTRLD	0x4
# define CTRLL	0xc
# define ALTS	0x0013
# define SHCHT	0x5a5b1b

#endif
