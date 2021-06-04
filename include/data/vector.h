#ifndef VECTOR_H_
#define VECTOR_H_

#include <include/util/types.h>

// integer unsigned
typedef struct 
{
	u32 x;
	u32 y;
	u32 z;
} vec3u;

// integer signed
typedef struct 
{
	i32 x;
	i32 y;
	i32 z;
} vec3i;

// Float
typedef struct 
{
	f32 x;
	f32 y;
	f32 z;
} vec3f;

// Double
typedef struct 
{
	f64 x;
	f64 y;
	f64 z;
} vec3d;



#endif
