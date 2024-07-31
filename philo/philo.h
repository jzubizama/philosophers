/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:08:52 by josu              #+#    #+#             */
/*   Updated: 2023/10/02 21:40:09 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<pthread.h>
# include<sys/time.h>

typedef struct s_input
{
	int		num_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		num_times_eat;
}			t_input;

typedef struct s_philo
{
	t_input			input;
	int				id;
	int				num_eaten;
	size_t			last_meal;
	size_t			init_time;
	int				*dead;
	pthread_t		th;
	pthread_mutex_t	fork;
	pthread_mutex_t	*dead_mut;
	pthread_mutex_t	*read_mut;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
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
void	*ft_philo(void *ptr);
int		ft_init_philo(int id, t_philo *philos, t_monitor *monit, t_input in);

void	*ft_monit(void *monit);
#endif