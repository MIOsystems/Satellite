#include <include/data/statistic.h>
#include <include/util/utility.h>


void statistic_calc_aggregate_val(stat_aggregate_f *data, f32 *new_val, u32 counter)
{
	// this means that it is the first message so dont do anything fancy with it
	if(counter == 0) 
	{
		data->total = *new_val;
		data->max = *new_val;
		data->avg = *new_val;
		data->min = *new_val;
	} else 
	{
		data->max = FIND_MAX(*new_val, data->max);
		data->min = FIND_MIN(*new_val, data->min);
		data->total += *new_val;
		data->avg = data->total / *new_val; 
	} 
}

void statistic_calc_aggregate_val_vec3f(stat_aggregate_f *data, vec3f *new_val, u32 counter)
{
	statistic_calc_aggregate_val(data, &new_val->x, counter);
	statistic_calc_aggregate_val(data, &new_val->y, counter);
	statistic_calc_aggregate_val(data, &new_val->z, counter);
}