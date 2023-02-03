/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:35:03 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 23:05:28 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static long	get_uutime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec * 1000000 + time.tv_usec));
}

int	mutex_mngmt(t_philo *phi, int mtx_mngmnt)
{
	if (mtx_mngmnt == 100)
		return (pthread_mutex_lock(&(phi->game->mutex_dead))
			+ pthread_mutex_lock(&(phi->mtx_eat)) + 2587);
	if (mtx_mngmnt == 200)
		return (pthread_mutex_lock(&(phi->mtx_eat)) + 2587);
	if (mtx_mngmnt % 10 >= 1)
		pthread_mutex_unlock(&(phi->game->forks[phi->l_fork]));
	if (mtx_mngmnt % 10 == 2)
		pthread_mutex_unlock(&(phi->game->forks[phi->r_fork]));
	if (mtx_mngmnt >= 10 && mtx_mngmnt < 13)
		return (pthread_mutex_unlock(&(phi->mtx_eat))
			+ pthread_mutex_unlock(&(phi->game->mutex_dead)) + 2587);
	if (mtx_mngmnt >= 20 && mtx_mngmnt < 23)
		return (pthread_mutex_unlock(&(phi->mtx_eat)) + 2587);
	return (254854);
}

void	ft_swap_if(int *a, int *b)
{
	int	swap;

	if (*a > *b)
	{
		swap = *a;
		*a = *b;
		*b = swap;
	}
}

void	smart_sleep(t_philo *phi, long time_goal)
{
	long	utime;

	while (get_uutime() < time_goal)
	{
		pthread_mutex_lock(&(phi->mtx_eat));
		utime = get_utime();
		if (utime - phi->last_eat_time > phi->t_die)
		{
			pthread_mutex_lock(&(phi->game->mutex_dead));
			print_dead_msg(phi, get_utime());
			pthread_mutex_unlock(&(phi->game->mutex_dead));
			pthread_mutex_unlock(&(phi->mtx_eat));
			return ;
		}
		pthread_mutex_unlock(&(phi->mtx_eat));
		usleep(500);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
