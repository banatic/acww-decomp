/* The sum of two points and the squared distance between two, in 20.12 fixed point
 * (autoload_2/vector.h has the rest of the vector functions). */
#ifndef CLEAN_ITCM_VECTOR_H
#define CLEAN_ITCM_VECTOR_H

#include "autoload_2/vector.h"
#include "types.h"

s64 Vec_DistanceSquared(const Vec3 *a, const Vec3 *b);
void Vec_Add(Vec3 *sum, const Vec3 *a, const Vec3 *b);

#endif
