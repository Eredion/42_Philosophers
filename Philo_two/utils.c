/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asegovia <asegovia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 09:44:23 by asegovia          #+#    #+#             */
/*   Updated: 2020/08/28 09:46:20 by asegovia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		min(int a, int b)
{
	return (a < b ? a : b);
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
