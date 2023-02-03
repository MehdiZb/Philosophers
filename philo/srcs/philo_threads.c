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

static int	routine_break(t_philo *phi, long actual_time, int mtx, char *state)
{
	mutex_mngmt(phi, 200);
	if (phi->phi_dead)
		return (mutex_mngmt(phi, 20 + mtx));
	if ((actual_time - phi->last_eat_time) > phi->t_die)
		return (print_dead_msg(phi, actual_time) + mutex_mngmt(phi, 20 + mtx));
	mutex_mngmt(phi, 20);
	if (state)
		print_state(phi, state, actual_time);
	if (phi->game->nb_philo_one == 1)
	{
		mutex_mngmt(phi, 100);
		usleep(phi->t_die * 1000);
		print_dead_msg(phi, get_utime());
		mutex_mngmt(phi, 10 + mtx);
		return (5);
	}
	return (0);
}

static int	routine_eat(t_game *game, t_philo *phi)
{
	pthread_mutex_lock(&(game->forks[phi->l_fork]));
	if (routine_break(phi, get_utime(), 1, STATE_FORK))
		return (1545);
	pthread_mutex_lock(&(game->forks[phi->r_fork]));
	phi->actual_time = get_utime();
	if (routine_break(phi, phi->actual_time, 2, STATE_FORK))
		return (1545);
	pthread_mutex_lock(&(phi->mtx_eat));
	phi->last_eat_time = phi->actual_time;
	pthread_mutex_unlock(&(phi->mtx_eat));
	if (routine_break(phi, phi->actual_time, 2, STATE_EAT))
		return (1545);
	smart_sleep(phi, phi->last_eat_time * 1000 + phi->t_eat * 1000);
	mutex_mngmt(phi, 2);
	return (0);
}

static void	*routine_while(t_game *game, t_philo *phi)
{
	while (1)
	{
		if (routine_eat(game, phi))
			return ((void *) NULL);
		phi->last_sleep_time = get_utime();
		if (routine_break(phi, phi->last_sleep_time, 0, STATE_SLEEP))
			return ((void *) NULL);
		pthread_mutex_lock(&(phi->mtx_eat));
		phi->eat_count++;
		pthread_mutex_unlock(&(phi->mtx_eat));
		smart_sleep(phi, phi->last_sleep_time * 1000 + phi->t_slp * 1000);
		if (routine_break(phi, get_utime(), 0, STATE_THINK))
			return ((void *) NULL);
	}
	return ((void *) NULL);
}

void	*routine(void *phi_param)
{
	t_philo	*phi;
	t_game	*game;

	phi = (t_philo *)phi_param;
	game = phi->game;
	pthread_mutex_lock(&(game->mtx_msg));
	pthread_mutex_unlock(&(game->mtx_msg));
	pthread_mutex_lock(&(game->mutex_dead));
	if (game->is_dead)
		return ((void *)(long)pthread_mutex_unlock(&(game->mutex_dead)) + 12);
	pthread_mutex_unlock(&(game->mutex_dead));
	pthread_mutex_lock(&(phi->mtx_eat));
	phi->last_eat_time = get_utime();
	pthread_mutex_unlock(&(phi->mtx_eat));
	if (phi->phil_id % 2)
		usleep(900);
	routine_while(game, phi);
	return ((void *) NULL);
}

void	print_state(t_philo *philo, char *state, long arg_time)
{
	int		cmpt;
	int		cmpt_state;
	long	time_now;

	cmpt = 0;
	pthread_mutex_lock(&(philo->game->mtx_msg));
	time_now = (arg_time - philo->game->start_time);
	pthread_mutex_unlock(&(philo->game->mtx_msg));
	add_nbr_str(philo->msg, time_now, &cmpt);
	add_nbr_str(philo->msg, philo->phil_id + 1, &cmpt);
	cmpt_state = 0;
	while (state[cmpt_state])
		philo->msg[cmpt++] = state[cmpt_state++];
	philo->msg[cmpt++] = 0;
	pthread_mutex_lock(&(philo->game->mtx_msg));
	if (philo->game->is_dead_msg == 42)
	{
		pthread_mutex_unlock(&(philo->game->mtx_msg));
		return ;
	}
	if (!ft_strcmp(state, STATE_DED))
		philo->game->is_dead_msg = 42;
	ft_putstr_fd(philo->msg, 1);
	pthread_mutex_unlock(&(philo->game->mtx_msg));
}
