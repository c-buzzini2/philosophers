/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:58 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/07 11:51:13 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_control_turns(void *arg)
{
	int avail_turns;
	int start;
	int	i;
	t_args *args;
	// t_waiter	*waiter;

	// waiter = ft_init_waiter();
	(void)arg;
	args = ft_args();
	start = 2 % args->nb_philo;
	while (1)
	{
		i = start;
		avail_turns = args->nb_philo / 2;
		while (avail_turns > 0)
		{
			pthread_mutex_lock(&args->waiter.waiter_mutex);
			if (args->waiter.kill_waiter == true)
			{
				//printf("exiting\n");
				pthread_mutex_unlock(&args->waiter.waiter_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&args->waiter.waiter_mutex);
			sem_wait(args->waiter_sem);
			sem_post(args->waiter.philo_sems[i]);
			i = (i + 2) % args->nb_philo;
			avail_turns--;
		}
		start = (start + 1) % args->nb_philo;
		usleep(1000);
	}
}

//START HERE!!! DO ALL THIS BEFORE THE FORKS, THEN EACH PROCESS FREES THE MEMORY BEFORE CONTINUING
//EXCEPT FOR PARENT, THEN, IN OPEN_TURN_SEMS, REMOVE O_CREATE

int	ft_allocate_waiter_arrays(t_args *args)
{
	int 	i;
	char	*id;
	int		j;
	
	args->waiter.philo_sems = malloc((args->nb_philo) * sizeof(sem_t *));
	if (args->waiter.philo_sems == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		return (1);
	}
	memset(args->waiter.philo_sems, 0, (args->nb_philo) * sizeof(sem_t *));
	args->waiter.sem_names = malloc((args->nb_philo) * sizeof(char*));
	if (args->waiter.sem_names == NULL)
	{
		ft_puterror("Allocation error");
		sem_close(args->print_sem);
		free(args->waiter.philo_sems);
		return (1);
	}
	i = 0;
	while (i < args->nb_philo)
	{
		args->waiter.sem_names[i] = malloc(20 * sizeof(char));
		if (args->waiter.sem_names[i] == NULL)
		{
			ft_puterror("Allocation error");
			j = 0;
			while (j < i)
				free(args->waiter.sem_names[j]);
			sem_close(args->print_sem);
			free(args->waiter.philo_sems);
			free(args->waiter.sem_names);
			return (1);
		}
		i++;
	}
	//memset(waiter->sem_names, 0, (args->nb_philo) * sizeof(char[20]));
	i = 0;
	while (i < args->nb_philo)
	{
		id = ft_itoa(i);
		ft_strlcpy(args->waiter.sem_names[i], "/turn_id_", 20);
		ft_strlcat(args->waiter.sem_names[i], id, 20);
		free(id);
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		if (i % 2 != 0)
			args->waiter.philo_sems[i] = sem_open(args->waiter.sem_names[i], O_CREAT, 0600, 1);
		else
			args->waiter.philo_sems[i] = sem_open(args->waiter.sem_names[i], O_CREAT, 0600, 0);
		if (args->waiter.philo_sems[i] == SEM_FAILED)
		{
			ft_puterror("sem_open failed\n");
			return(1);
		}
		i++;
	}
	return (0);
}
// t_waiter	*ft_init_waiter()
// {
// 	static t_waiter	waiter;

// 	return (&waiter);
// }

int	ft_thread_waiter(t_waiter *waiter)
{
	if (pthread_create(&waiter->w_thread, NULL, ft_control_turns, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		return (1);
	}
	return (0);
}
int	ft_waiter(t_args *args)
{
	//t_waiter	*waiter;
	
	//waiter = ft_init_waiter();
	//waiter->kill_waiter = false;
	//ft_allocate_waiter_arrays(args, waiter); //error check!!!
	if (pthread_mutex_init(&args->waiter.waiter_mutex, NULL) != 0)
	{
		ft_puterror("Could not initialize mutex");
		return (1);
	}
	ft_thread_waiter(&args->waiter);
	return (0);
}