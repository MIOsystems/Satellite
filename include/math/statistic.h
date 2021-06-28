#ifndef STATISTIC_H_
#define STATISTIC_H_

#include <include/math/vector.h>
#include <include/util/types.h>

typedef struct 
{
	f32 total;
	u32 count;
	f32 avg;
	f32 min;
	f32 max;
} AggregateStateFloat_t;

/**
 * This function will calculate the min, max and avg and store it in the data struct
 * @param data the statistisc struct that you want to store it in
 * @param new_val the new values that you want to add/analyze
 * @param total a counter that it requires, which you have to manually count
 * the counter has to start on zero, so example:
 * 
 * u32 counter = 0;
 * poll();
 * statistic_calc_aggregate_val();
 * counter++;
 */
void statisticCalcAggregateValues(AggregateStateFloat_t *data, f32 *new_val, u32 counter);

void statisticReset(AggregateStateFloat_t *data);

#endif
