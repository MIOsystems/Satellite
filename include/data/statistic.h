#ifndef STATISTIC_H_
#define STATISTIC_H_

#include <include/util/types.h>
#include <include/data/vector.h>

typedef struct 
{
	f32 total;
	u32 avg;
	u32 min;
	u32 max;
} stat_aggregate_u;

typedef struct 
{
	f32 total;
	i32 avg;
	i32 min;
	i32 max;
} stat_aggregate_i;

typedef struct 
{
	f32 total;
	f32 avg;
	f32 min;
	f32 max;
} stat_aggregate_f;

typedef struct 
{
	f64 avg;
	f64 min;
	f64 max;
} stat_aggregate_d;

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
void statistic_calc_aggregate_val(stat_aggregate_f *data, f32 *new_val, u32 counter);

/**
 * This function will calculate the min, max and avg and store it in the data struct
 * @param data the statistisc struct that you want to store it in
 * @param new_val  the new vec3f values that you want to add/analyze
 * @param total a counter that it requires, which you have to manually count
 * the counter has to start on zero, so example:
 * 
 * u32 counter = 0;
 * poll();
 * statistic_calc_aggregate_val();
 * counter++;
 */
void statistic_calc_aggregate_val_vec3f(stat_aggregate_f *data, vec3f *new_val, u32 counter);

#endif
