/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:35:03 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 23:05:28 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_rules(t_game *game, int ac, char **av)
{
	int	control;

	control = 0;
	game->nb_philo = ft_atoi(av[1], &control) * 1;
	game->nb_philo_one = game->nb_philo;
	game->t_die = ft_atoi(av[2], &control) * 1;
	game->t_eat = ft_atoi(av[3], &control) * 1;
	game->t_slp = ft_atoi(av[4], &control) * 1;
	if (ac == 6)
	{
		game->max_eat = ft_atoi(av[5], &control);
		game->ini_max_eat = 1;
	}
	if (control)
		return (-1);
	return (0);
}

static int	init_threads(t_game *game)
{
	int	cmpt;

	cmpt = -1;
	pthread_mutex_lock(&(game->mtx_msg));
	while (++cmpt < game->nb_philo)
	{
		game->philos[cmpt].t_die = game->t_die;
		game->philos[cmpt].t_eat = game->t_eat;
		game->philos[cmpt].t_slp = game->t_slp;
		game->philos[cmpt].phil_id = cmpt;
		game->philos[cmpt].thr_ret
			= pthread_create(&(game->philos[cmpt].thr_philo),
				NULL, &routine, &(game->philos[cmpt]));
		if (game->philos[cmpt].thr_ret)
		{
			game->is_dead = 1;
			printf("crash a la creation du philo %d\n", cmpt + 1);
			return (pthread_mutex_unlock(&(game->mtx_msg)) - 2588);
		}
	}
	game->start_time = get_utime();
	pthread_mutex_unlock(&(game->mtx_msg));
	check_eat_death(game);
	return (0);
}

static int	init_philo_forks(t_game *game)
{
	int	cmpt;

	cmpt = -1;
	while (++cmpt < game->nb_philo)
		if (ini_forks_while(game, cmpt))
			return (-3);
	game->mtx_forks_ret = -1;
	while (++game->mtx_forks_ret < game->nb_philo)
		if (pthread_mutex_init(&(game->forks[game->mtx_forks_ret]), NULL))
			return (-4);
	if (pthread_mutex_init(&(game->mutex_dead), NULL))
		return (-4);
	game->mtx_dead_ret = 2;
	if (pthread_mutex_init(&(game->mtx_msg), NULL))
		return (-4);
	game->mtx_msg_ret = 2;
	return (0);
}

int	print_dead_msg(t_philo *philo, long actual_time)
{
	if (philo->game->is_dead)
		return (1);
	philo->game->is_dead = 1;
	print_state(philo, STATE_DED, actual_time);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_bzero(&game, sizeof(game));
	if (ac < 5 || ac > 6)
		return (philo_err(NULL, ERR_AC));
	if (init_rules(&game, ac, av))
		return (philo_err(&game, ERR_AV_FORMAT));
	if (game.nb_philo > 200)
		return (philo_err(&game, ERR_MAX_PHI));
	if (game.nb_philo == 0 || (game.ini_max_eat && !game.max_eat))
		return (0);
	if (init_philo_forks(&game))
		return (philo_err(&game, ERR_FORKS_INI));
	if (init_threads(&game))
		return (philo_err(&game, ERR_THREADS_INI));
	philo_free(&game);
	return (0);
}
