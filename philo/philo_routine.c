/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:36:00 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/20 09:18:11 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_eat(t_philo *arg)
{
	pthread_mutex_lock(((*arg).l_fork));
	ft_print_change("has taken a fork", arg);
	if (arg->input.num_philo == 1)
	{
		ft_usleep(arg->input.t_die);
		pthread_mutex_unlock(((*arg).l_fork));
		return ;
	}
	pthread_mutex_lock(((*arg).r_fork));
	ft_print_change("has taken a fork", arg);
	pthread_mutex_lock(((*arg).read_mut));
	(*arg).num_eaten++;
	(*arg).last_meal = get_current_time();
	ft_print_change("is eating", arg);
	pthread_mutex_unlock(((*arg).read_mut));
	ft_usleep(arg->input.t_eat);
	pthread_mutex_unlock(((*arg).l_fork));
	pthread_mutex_unlock(((*arg).r_fork));
}

int	ft_read_dead(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(philo->dead_mut);
	if (*(philo->dead) == 1)
		ret = 1;
	pthread_mutex_unlock(philo->dead_mut);
	return (ret);
}

void	*ft_philo(void *ptr)
{
	t_philo	*arg;

	arg = (t_philo *)ptr;
	if ((*arg).id % 2 != 0)
		usleep(10);
	while (!ft_read_dead(arg))
	{
		ft_eat(arg);
		ft_print_change("is sleeping", arg);
		ft_usleep(arg->input.t_sleep);
		ft_print_change("is thinking", arg);
	}
	return (NULL);
}

int	ft_init_philo(int id, t_philo *philos, t_monitor *monit, t_input in)
{
	philos->input.num_philo = in.num_philo;
	philos->input.t_die = in.t_die;
	philos->input.t_eat = in.t_eat;
	philos->input.t_sleep = in.t_sleep;
	philos->input.num_times_eat = in.num_times_eat;
	(*philos).id = id;
	(*philos).init_time = get_current_time();
	(*philos).last_meal = get_current_time();
	(*philos).num_eaten = 0;
	(*philos).dead = &(*monit).dead;
	(*philos).dead_mut = &(*monit).dead_mut;
	(*philos).read_mut = &(*monit).read_mut;
	if (pthread_mutex_init(&(*philos).fork, NULL) != 0)
		return (1);
	(*philos).l_fork = &(*philos).fork;
	if (id != in.num_philo - 1)
		(*philos).r_fork = &(*(philos + 1)).fork;
	else
		(*philos).r_fork = &(*(philos - (in.num_philo - 1))).fork;
	if (pthread_create(&(*philos).th, NULL, &ft_philo, philos) != 0)
		return (2);
	return (0);
}
