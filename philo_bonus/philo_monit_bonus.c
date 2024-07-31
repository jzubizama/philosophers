/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monit_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:38:45 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/20 09:57:39 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philobonus.h"

int	ft_check_dead(t_philo *philo)
{
	sem_wait(philo->input->sem_read);
	if (get_current_time() - philo->last_meal
		>= (size_t)philo->input->t_die)
	{
		sem_post(philo->input->sem_read);
		sem_wait(philo->input->sem_print);
		ft_print_change("died", philo);
		sem_wait(philo->input->sem_dead);
		(philo->dead) = 1;
		sem_post(philo->input->sem_dead);
		return (1);
	}
	sem_post(philo->input->sem_read);
	return (0);
}

int	ft_check_meals(t_philo *philo)
{
	if (philo->input->num_times_eat < 0)
		return (0);
	sem_wait(philo->input->sem_read);
	if (philo->num_eaten < philo->input->num_times_eat)
	{
		sem_post(philo->input->sem_read);
		return (0);
	}
	sem_post(philo->input->sem_read);
	sem_wait(philo->input->sem_dead);
	(philo->dead) = 1;
	sem_post(philo->input->sem_dead);
	return (1);
}

void	*ft_monit(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_check_dead(philo))
		{
			exit (1);
		}
		else if (ft_check_meals(philo))
		{
			sem_post(philo->input->sem_fork);
			sem_post(philo->input->sem_fork);
			exit (0);
		}
	}
	return (NULL);
}

int	ft_init_monit(t_monitor *monit, t_philo *philos)
{
	if (pthread_mutex_init(&monit->dead_mut, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&monit->read_mut, NULL) != 0)
		return (2);
	monit->dead = 0;
	monit->philos = philos;
	return (0);
}

void	ft_sem_create(t_input *in)
{
	sem_unlink("fork");
	sem_unlink("death");
	sem_unlink("read");
	sem_unlink("stop");
	sem_unlink("print");
	sem_unlink("meal");
	in->sem_fork = sem_open("fork", O_CREAT, 0600, in->num_philo);
	in->sem_dead = sem_open("death", O_CREAT, 0600, 1);
	in->sem_read = sem_open("read", O_CREAT, 0600, 1);
	in->sem_print = sem_open("print", O_CREAT, 0600, 1);
	in->sem_meal = sem_open("meal", O_CREAT, 0600, 0);
}
