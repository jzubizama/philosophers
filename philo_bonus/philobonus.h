/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philobonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:08:52 by josu              #+#    #+#             */
/*   Updated: 2023/11/20 09:58:07 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOBONUS_H
# define PHILOBONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_input
{
	int		num_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		num_times_eat;
	sem_t	*sem_fork;
	sem_t	*sem_dead;
	sem_t	*sem_read;
	sem_t	*sem_print;
	sem_t	*sem_meal;
}			t_input;

typedef struct s_philo
{
	t_input			*input;
	int				id;
	int				num_eaten;
	size_t			last_meal;
	size_t			init_time;
	int				dead;
	int				pid;
}					t_philo;

typedef struct s_monitor
{
	int				dead;
	pthread_t		th;
	pthread_mutex_t	dead_mut;
	pthread_mutex_t	read_mut;
	t_philo			*philos;
}					t_monitor;

size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	ft_print_change(char *str, t_philo *philo);
void	ft_destroy_mut(t_philo	*philos, t_monitor *monit);

int		ft_read_dead(t_philo *philo);
void	ft_philo(t_philo *arg);
t_philo	*ft_philo_init(t_input *in);

void	*ft_monit(void *monit);
void	ft_sem_create(t_input *in);
int		ft_init_monit(t_monitor *monit, t_philo *philos);

void	ft_destroy_sem(t_input *in);
#endif