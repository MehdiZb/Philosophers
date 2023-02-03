/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:35:03 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 23:05:28 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	free_thread_mutex(t_game *game)
{
	int	cmpt;

	cmpt = 0;
	if (game)
	{
		while (cmpt < game->nb_philo && !game->philos[cmpt].thr_ret)
			pthread_join(game->philos[cmpt++].thr_philo, NULL);
		cmpt = 0;
		while (cmpt < game->mtx_forks_ret)
			pthread_mutex_destroy(&(game->forks[cmpt++]));
		cmpt = 0;
		while (cmpt < game->nb_philo && !game->philos[cmpt].mtx_eat_ret)
			pthread_mutex_destroy(&(game->philos[cmpt++].mtx_eat));
		if (game->mtx_dead_ret == 2)
			pthread_mutex_destroy(&(game->mutex_dead));
		if (game->mtx_msg_ret == 2)
			pthread_mutex_destroy(&(game->mtx_msg));
	}
}

int	philo_err(t_game *game, char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	philo_free(game);
	return (-1);
}

void	philo_free(t_game *game)
{
	if (game)
	{
		free_thread_mutex(game);
	}
}
