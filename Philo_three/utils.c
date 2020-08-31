/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 11:53:07 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/28 11:55:03 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		eat_action(t_philo *phil)
{
	if (phil->eat_counter > 0)
		--phil->eat_counter;
	if (phil->eat_counter == 0)
		return (0);
	else
		return (1);
}

int		max(int a, int b)
{
	return (a > b ? a : b);
}

void	ft_putchar(char a)
{
	write(1, &a, 1);
}

void	putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		++str;
	}
}

void	putnbr(unsigned long nb)
{
	if (nb >= 10)
		putnbr(nb / 10);
	ft_putchar((nb % 10) + '0');
}
