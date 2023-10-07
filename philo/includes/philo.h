/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:16:11 by omer/baha         #+#    #+#             */
/*   Updated: 2023/10/07 12:16:08 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define EAT "\033[1;93mis eating 🍝\033[0;39m\n"
# define SLEEP "\033[1;95mis sleeping 🌙\033[0;39m\n"
# define THINK "\033[1;90mis thinking 💭\033[0;39m\n"
# define TAKE_FORK "\033[1;94mhas taken a fork 🍴\033[0;39m\n"
# define DIE "\033[1;91mdied 💀\033[0;39m\n"

# include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	int				nb_eat;
	int				dead;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	nb_eat_mutex;
	pthread_mutex_t	last_eat_mutex;
	pthread_t		monitor;
	t_philo			*philo;
}	t_table;

struct s_philo
{
	int			id;
	int			nb_eat;
	long		last_eat;
	t_table		*table;
	pthread_t	thread;
};

void	*routine(void *arg);
int		ft_init_philo(t_table *table);
int		ft_check_dead_philo(t_table *table);
int		ft_init_table(t_table *table, int argc, char **argv);
int		ft_print(t_philo *philo, char *str);
long	philo_get_time(void);
int		ft_atoi(const char *str);
void	*monitor(t_table *table);
int		ft_eat_goal(t_table *table);
void	my_sleep(long long time);

#endif