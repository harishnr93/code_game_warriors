#include "../include/my_core_bot.h"


int	is_warriors(t_obj *unit)
{
	return (unit->state == STATE_ALIVE
		&& unit->type == OBJ_UNIT
		&& unit->s_unit.type_id == UNIT_WARRIOR);
}

t_obj	**ft_get_warriors_sorted(t_obj **units, int order, int *war_count)
{
	t_obj *my_core = ft_get_my_core();

	if (!my_core || !units)
		return (NULL);

	// Count warriors
	int warrior_count = *war_count;
	int i = 0;
	while (units[i] != NULL)
	{

		if (is_warriors(units[i]))
		{
			// printf("Line 26   \n");
			warrior_count++;
		}
		i++;
	}
	// printf("Line 31  =%d \n", i);
	// Allocate memory for warriors array

	// t_obj *warriors = malloc(sizeof(t_obj) * (warrior_count));
	
	t_obj **warriors = malloc(sizeof(t_obj *) * (warrior_count + 1));
	//t_obj **warriors = malloc(sizeof(t_obj *) * (warrior_count + 1));
	if (!warriors)
	{
		return (NULL);
	}

	// Fill warriors array
	int j = 0;
	i = 0;
	while (units[i] != NULL)
	{
		if (is_warriors(units[i]))
		{
			// printf("Line 47  id=%ld order=%d\n", units[i]->id, order);
			warriors[j++] = units[i];
		}
		i++;
	}
	warriors[j] = NULL;
	// t_obj t;
	// t = NULL;
	// warriors[j] =  *(NULL); // NULL terminate the array

	// bubble sort)
	i = 0;
	while (i < warrior_count - 1)
	{
		j = 0;
		while (j < warrior_count - i - 1)
		{
			// printf("Line 62   \n");
			if ((order * ft_distance(my_core, warriors[j])) > (order
					* ft_distance(my_core, warriors[j + 1])))
			{
				t_obj *temp = warriors[j];
				warriors[j] = warriors[j + 1];
				warriors[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	// printf("End sorting warrior_count=%d   \n", warrior_count);
	*war_count = warrior_count;

	return (warriors);
}