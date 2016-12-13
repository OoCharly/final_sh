/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_linux.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:51:46 by tboos             #+#    #+#             */
/*   Updated: 2016/12/13 11:20:41 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_MAC_H
# define KEYS_MAC_H

/*
** SIGNAL UNDEFINE ON MAC
*/
# define SIGSTKFLT 0

/*
** TAKE KEY_LINUX_H FOR REFERENCE
** all CTRL are replaced by ALT on mac
*/
# define CLF	0x0A
# define SUP	0x7E335B1B
# define CHT	0x09
# define DEL	0x7F
# define LEF	0x445B1B
# define RIG	0x435B1B
# define UPP	0x415B1B
# define DOW	0x425B1B
# define CLEF	0x445B1B1B
# define CUPP	0x415B1B1B
# define CRIG	0x435B1B1B
# define CDOW	0x425B1B1B
# define CRS	0x12
# define END	0x465B1B
# define HOM	0x485B1B
# define NUL	0x00
# define ESC	0x1B
# define CTRLD	0x4
# define ALTS	0x92C3
# define SHCHT	0x5A5B1B

#endif
