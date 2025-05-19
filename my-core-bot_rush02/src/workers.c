/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnataraj <hnataraj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 00:20:39 by hnataraj          #+#    #+#             */
/*   Updated: 2025/05/19 15:30:45 by hnataraj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/my_core_bot.h"

void	worker_combine(t_obj *worker)
{
	t_obj	*resource;

	resource = ft_get_nearest_resource(worker);
	if (resource)
		ft_travel_attack(worker, resource);
	else
		ft_travel_attack(worker, ft_get_first_opponent_core());
}
