/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:35:03 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 23:05:28 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	if (str)
		write(fd, str, len);
}

unsigned int	ft_atoi(const char *str, int *control)
{
	unsigned int	cmpt;
	unsigned int	res;

	cmpt = 0;
	res = 0;
	while ((str[cmpt] > 8 && str[cmpt] < 14) || str[cmpt] == 32)
		cmpt++;
	while (str[cmpt] > 47 && str[cmpt] < 58)
	{
		if (res > 214748364 || (res == 214748364 && (str[cmpt] - 48) > 7))
			*control = -1;
		res = (res * 10) + (str[cmpt++] - 48);
	}
	if (str[cmpt])
		*control = -1;
	return (res);
}

void	ft_bzero(void *ptr, size_t size)
{
	unsigned char	*dest;
	size_t			i;

	dest = (unsigned char *)ptr;
	i = 0;
	while (i++ < size)
		*dest++ = 0;
}

long	get_utime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

void	add_nbr_str(char *str, long nbr, int *cmpt)
{
	long	cpy_time;
	int		cmpt_num;

	cpy_time = nbr;
	cmpt_num = *cmpt;
	while (cpy_time > 9)
	{
		++cmpt_num;
		cpy_time = cpy_time / 10;
	}
	*cmpt = cmpt_num + 1;
	cpy_time = nbr;
	while (nbr > 9)
	{
		str[cmpt_num--] = "0123456789"[nbr % 10];
		nbr = nbr / 10;
	}
	str[cmpt_num] = "0123456789"[nbr % 10];
	str[(*cmpt)++] = ' ';
}
