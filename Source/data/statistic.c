#include <include/data/statistic.h>
#include <include/util/utility.h>


void statistic_calc_aggregate_val(stat_aggregate_f *data, f32 *new_val, u32 counter)
{
	data->total += *new_val;
	// this means that it is the first message so dont do anything fancy with it
	if(counter == 0) 
	{
		data->max = *new_val;
		data->avg = *new_val;
		data->min = *new_val;
	} else 
	{

		if(data->max < *new_val)
		{
			data->max = *new_val;
		}
		// If it is a new max value then don't check if its a new minimum value, but if it is not a new max value check the old value
		else if(data->min >  *new_val) {
			data->min  =  *new_val;
		}
		// always add calculate the new average no matter if there is a new minimum or max
		data->avg = ( data->total /counter);
	} 
}

void statistic_calc_aggregate_val_vec3f(stat_aggregate_f *data, vec3f *new_val, u32 counter)
{
	statistic_calc_aggregate_val(data, &new_val->x, counter);
	statistic_calc_aggregate_val(data, &new_val->y, counter);
	statistic_calc_aggregate_val(data, &new_val->z, counter);
}
