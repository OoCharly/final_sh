/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 19:54:02 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/06 20:26:29 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_set_handlers(void)
{
	if (SIG_ERR == signal(SIGQUIT, &ft_exit_supervisor)
		&& ft_error(SHNAME, "supervisor", "signal set", CR_ERROR))
		return (0);
	return (1);
}
