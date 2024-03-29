#include <include/math/statistic.h>
#include <include/util/utility.h>


void statisticCalcAggregateValues(AggregateStateFloat_t *data, f32 *new_val, u32 counter)
{
	data->count = counter;
	// this means that it is the first message so dont do anything fancy with it
	if(counter == 0) 
	{
		data->total += *new_val;
		data->max = *new_val;
		data->avg = *new_val;
		data->min = *new_val;
	} else 
	{
		data->total += *new_val;
		if(data->max < *new_val)
		{
			data->max = *new_val;
		}
		// If it is a new max value then don't check if its a new minimum value, but if it is not a new max value check the old value
		else if(data->min >  *new_val) {
			data->min  =  *new_val;
		}
		// always add calculate the new average no matter if there is a new minimum or max
		data->avg = (data->total / (f32) (data->count));
	} 
}

void statisticReset(AggregateStateFloat_t *data)
{
	data->count = 0;
	data->total = 0;
	data->max = 0;
	data->avg = 0;
	data->min = 0;
}
