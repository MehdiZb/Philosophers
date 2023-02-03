/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_eat_death.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:35:03 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 23:05:28 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_eat_death_part_two(t_game *game, int cmpt)
{
	if (cmpt == game->nb_philo)
		return (15);
	pthread_mutex_lock(&(game->mutex_dead));
	if (game->is_dead)
		return (pthread_mutex_unlock(&(game->mutex_dead)) + 456);
	pthread_mutex_unlock(&(game->mutex_dead));
	cmpt = -1;
	while (++cmpt < game->nb_philo)
	{
		pthread_mutex_lock(&(game->philos[cmpt].mtx_eat));
		if ((get_utime() - game->philos[cmpt].last_eat_time > game->t_die)
			&& game->philos[cmpt].last_eat_time)
		{
			pthread_mutex_lock(&(game->mutex_dead));
			print_dead_msg(&(game->philos[cmpt]), get_utime());
			pthread_mutex_unlock(&(game->mutex_dead));
			pthread_mutex_unlock(&(game->philos[cmpt].mtx_eat));
			return (456);
		}
		pthread_mutex_unlock(&(game->philos[cmpt].mtx_eat));
		usleep(40);
	}
	return (0);
}

static void	set_phi_dead(t_game *game)
{
	int	cmpt;

	cmpt = -1;
	while (++cmpt < game->nb_philo)
	{
		pthread_mutex_lock(&(game->philos[cmpt].mtx_eat));
		game->philos[cmpt].phi_dead = 1;
		pthread_mutex_unlock(&(game->philos[cmpt].mtx_eat));
	}
}

int	check_eat_death(t_game *game)
{
	int		cmpt;

	while (1)
	{
		cmpt = -1;
		while (++cmpt < game->nb_philo && game->ini_max_eat)
		{
			pthread_mutex_lock(&(game->philos[cmpt].mtx_eat));
			if ((game->philos[cmpt].eat_count < game->max_eat))
			{
				pthread_mutex_unlock(&(game->philos[cmpt].mtx_eat));
				break ;
			}
			pthread_mutex_unlock(&(game->philos[cmpt].mtx_eat));
		}
		if (check_eat_death_part_two(game, cmpt))
			break ;
	}
	set_phi_dead(game);
	pthread_mutex_lock(&(game->mutex_dead));
	game->all_eat = 1;
	pthread_mutex_unlock(&(game->mutex_dead));
	return (1);
}

int	ini_forks_while(t_game *game, int cmpt)
{
	ft_bzero(&(game->philos[cmpt]), sizeof(game->philos[cmpt]));
	game->philos[cmpt].game = game;
	game->philos[cmpt].l_fork = cmpt;
	game->philos[cmpt].r_fork = (cmpt + 1) % game->nb_philo;
	ft_swap_if(&(game->philos[cmpt].r_fork), &(game->philos[cmpt].l_fork));
	if (cmpt + 1 == game->nb_philo && game->nb_philo > 1
		&& game->nb_philo % 2 == 1)
		ft_swap_if(&(game->philos[cmpt].l_fork), &(game->philos[cmpt].r_fork));
	game->philos[cmpt].mtx_eat_ret
		= pthread_mutex_init(&(game->philos[cmpt].mtx_eat), NULL);
	if (game->philos[cmpt].mtx_eat_ret)
		return (-3);
	return (0);
}
