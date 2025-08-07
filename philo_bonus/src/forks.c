/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:28:34 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/08/07 17:02:02 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
//START HERE!!!! Fork processes, wait[id, graceful termination]

void	ft_change_boolean(t_pids *pids, int exited, t_args *args)
{
	int i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pids[i].pid == exited)
		{
			pids[i].exited = true;
			break ;
		}
		i++;
	}
}

void	ft_kill_remaining_processes(t_pids *pids, t_args *args)
{
	int i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pids[i].exited == false)
			kill(pids[i].pid, SIGKILL);
		i++;
	}
}

int	ft_parent(t_args *args, t_pids *pids)
{
	int		e_status;
	int		exited_pid;
	int		e_code;
	int		exited_count;
	//t_waiter	*waiter;

	exited_count = 0;
	while (exited_count < args->nb_philo)
	{
		exited_pid = waitpid(-1, &e_status, 0);
		
		//long timestamp = ft_timestamp_ms();
		//printf("%ld: process %d exited\n", timestamp, exited_pid);

		if (exited_pid > 0)
		{
			exited_count++;
			ft_change_boolean(pids, exited_pid, args);
			if (WIFEXITED(e_status)) 
			{
				e_code = WEXITSTATUS(e_status);
				//printf("exit code: %d\n", e_code);
				if (e_code == 2 || e_code == 3) 
					ft_kill_remaining_processes(pids, args);
			}
		}
	}
	//waiter = ft_init_waiter();
	//long timestamp = ft_timestamp_ms();
	//printf("%ld: processes exited\n", timestamp);
	//printf("processes exited\n");

	
	pthread_mutex_lock(&args->kill_mutex);
	args->kill_waiters = true;
	pthread_mutex_unlock(&args->kill_mutex);
	int i = 0;
	while (i < args->nb_philo)
	{
		sem_post(args->all_waiter_sems[i]);
		sem_post(args->all_waiter_sems[i]);//2x?
	}
	i = 0;
	// pthread_join(args->waiter.w_thread, NULL);
	while (i < args->nb_philo)
		pthread_join(args->w_threads[i++], NULL);
	free(pids);
	ft_close_parent();
	pthread_mutex_destroy(&args->kill_mutex);

	return (0);
}

t_philo	*ft_create_philo(void)
{
	static t_philo	philo;

	return (&philo);
}

t_pids	*ft_allocate_pids(t_args *args)
{
	t_pids	*pids;
	
	pids = malloc(args->nb_philo * sizeof(t_pids));
	if (pids == NULL)
	{
		perror("Error in allocation");
		sem_close(args->print_sem);
		ft_unlink_semaphores();
		exit(1);
	}
	return (pids);
}

int	ft_forks(t_args *args)
{
	int		id;
	int		forks;
	t_philo	*philo;
	t_pids	*pids;
	int		i;		

	i = 0;
	forks = 0;
	pids = ft_allocate_pids(args);
	ft_allocate_waiter_arrays(args);//error check
	gettimeofday(&args->start_time, NULL);
	args->start_time.tv_usec += 5000; // Add 5ms delay
	if (args->start_time.tv_usec >= 1000000) {
		args->start_time.tv_sec += 1;
		args->start_time.tv_usec -= 1000000;
	}
	while (forks < args->nb_philo)
	{
		id = fork();
		if (id == -1)
		{
			perror("Error in the fork");
			sem_close(args->print_sem);
			ft_unlink_semaphores();
			exit(1);
		}
		if (id == 0)
		{
			free(pids);
			ft_close_parent();
			philo = ft_create_philo();
			philo->id = forks;
			if (ft_mutex_and_thread(philo) == 1)
				return (3);
			ft_open_philo_sems(philo);
			ft_start_routine(philo);
		}
		else
		{
			pids[i].pid = id;
			pids[i].exited = false;
		}
		forks++;
		i++;
	}
	ft_waiter(args);//handle error return 1
	return (ft_parent(args, pids));
}
