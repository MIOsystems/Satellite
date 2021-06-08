#ifndef VECTOR_H_
#define VECTOR_H_

#include <include/util/types.h>

// integer unsigned
typedef struct 
{
	u32 x;
	u32 y;
	u32 z;
} Vec3u_t;

// integer signed
typedef struct 
{
	i32 x;
	i32 y;
	i32 z;
} Vec3i_t;

// Float
typedef struct 
{
	f32 x;
	f32 y;
	f32 z;
} Vec3f_t;

// Double
typedef struct 
{
	f64 x;
	f64 y;
	f64 z;
} Vec3d_t;



#endif
