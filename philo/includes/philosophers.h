/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:35:59 by mzblah            #+#    #+#             */
/*   Updated: 2022/03/30 20:19:40 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*
**  INCLUDES
*/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

/*
**  DEFINES
*/

# define ERR_AC "Wrong numbers of arguments.\n"
# define ERR_INIT_RULES "rules initialisation failed.\n"
# define ERR_AV_FORMAT "Arguments must be an int32 positive numbers only.\n"
# define ERR_FORKS_INI "Erreur lors de l'initialisation des forks\n"
# define ERR_THREADS_INI "Erreur lors de l'initialisation des threads\n"
# define ERR_MAX_PHI "200 philosophers maximum.\n"

# define STATE_FORK "has taken a fork\n"
# define STATE_EAT "is eating\n"
# define STATE_SLEEP "is sleeping\n"
# define STATE_THINK "is thinking\n"
# define STATE_DED "died\n"

/*
**  STRUCTURES
*/

typedef struct s_philosophers
{
	int					t_die;
	int					t_eat;
	int					t_slp;
	int					l_fork;
	int					r_fork;
	long				actual_time;
	long				last_eat_time;
	long				last_sleep_time;
	int					eat_count;
	int					phil_id;
	int					phi_dead;
	char				msg[100];
	int					mtx_eat_ret;
	pthread_mutex_t		mtx_eat;
	int					thr_ret;
	pthread_t			thr_philo;
	struct s_philo_game	*game;
}				t_philo;

typedef struct s_philo_game
{
	pthread_mutex_t	test;

	long			start_time;
	int				nb_philo;
	int				nb_philo_one;
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				max_eat;
	int				ini_max_eat;
	int				all_eat;
	int				is_dead;
	int				is_dead_msg;
	int				start;
	int				mtx_msg_ret;
	pthread_mutex_t	mtx_msg;
	int				mtx_dead_ret;
	pthread_mutex_t	mutex_dead;
	int				mtx_forks_ret;
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
}				t_game;

/*
**  PROTOTYPES
*/

void			ft_putstr_fd(char *s, int fd);
void			ft_bzero(void *b, size_t n);
unsigned int	ft_atoi(const char *str, int *control);
long			get_utime(void);
void			add_nbr_str(char *str, long nbr, int *cmpt);

int				philo_err(t_game *rules, char *err_msg);
void			philo_free(t_game *rules);

void			*routine(void *phi_param);
void			print_state(t_philo *philo, char *state, long arg_time);

int				print_dead_msg(t_philo *philo, long actual_time);

void			smart_sleep(t_philo *phi, long time_goal);
void			ft_swap_if(int *a, int *b);
int				mutex_mngmt(t_philo *phi, int mtx_mngmnt);
int				ft_strcmp(char *s1, char *s2);

int				check_eat_death(t_game *game);
int				ini_forks_while(t_game *game, int cmpt);

#endif
