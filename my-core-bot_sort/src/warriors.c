#include "../include/my_core_bot.h"

void	fight(t_obj	**our_warriors, int our_count, t_obj	**opponent_warriors, int opponent_count)
{
	// int	**distances;
	int	i;
	int	j;
	int	count_fighters;
	int	cur_count_fighters;

	// printf("FIGHT START our_count=%d     opponent_count=%d\n", our_count, opponent_count);
	(void )opponent_warriors;


	count_fighters = 3;
	// i = 0;
	// distances = malloc((our_count + 1) * sizeof(int *));
	// while (i < our_count)
	// {
	// 	distances[i] = malloc((opponent_count + 1) * sizeof(int));
	// 	if (distances[i] == NULL)
	// 		return (0);
	// 	i++;
	// }
	i = 0;
	
	cur_count_fighters = 0;
	// printf("fight=%d  %d\n", our_count, opponent_count);
	j = opponent_count;
	j = 0;
	while (i < our_count)
	{

			// (void) our_warriors;
			// (void) opponent_warriors; i++;
		// printf("Id=%ld attack id=%ld       i=%d    our_count =%d\n", our_warriors[i]->id, opponent_warriors[j]->id, i, our_count);
		ft_travel_attack(our_warriors[i++], opponent_warriors[j]);
		// ft_travel_attack(our_warriors[i], ft_get_nearest_opponent_unit(our_warriors[i]));
		i++;
		cur_count_fighters++;
		if (cur_count_fighters >= count_fighters)
		{
			j++;
			cur_count_fighters = 0;
		}
		
		
	}

	return ;
}