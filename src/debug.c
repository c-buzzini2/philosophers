	// if (id % 2 != 0)
	// {
	// 	first = id;
	// 	second = l_philo;
	// 	while (1)
	// 	{
	// 		if (ft_check_death_flag() == 2)
	// 			return (2);
	// 		pthread_mutex_lock(&arrays->philos[id].turn_mutex);
	// 		if(arrays->philos[id].own_turn == 1)
	// 		{
	// 			pthread_mutex_lock(&arrays->philos[l_philo].turn_mutex);
	// 			if(arrays->philos[l_philo].own_turn == 0)
	// 				break ;
	// 			pthread_mutex_unlock(&arrays->philos[l_philo].turn_mutex);
	// 		}
	// 		pthread_mutex_unlock(&arrays->philos[id].turn_mutex);
	// 		usleep(100);
	// 	}
	// }
	// else
	// {
	// 	first = l_philo;
	// 	second = id;
	// 	while (1)
	// 	{
	// 		if (ft_check_death_flag() == 2)
	// 			return (2);
	// 		pthread_mutex_lock(&arrays->philos[l_philo].turn_mutex);
	// 		if(arrays->philos[l_philo].own_turn == 1)
	// 		{
	// 			pthread_mutex_lock(&arrays->philos[id].turn_mutex);
	// 			if(arrays->philos[id].own_turn == 0)
	// 				break ;
	// 			pthread_mutex_unlock(&arrays->philos[id].turn_mutex);
	// 		}
	// 		pthread_mutex_unlock(&arrays->philos[l_philo].turn_mutex);
	// 		usleep(100);
	// 	}
	// }