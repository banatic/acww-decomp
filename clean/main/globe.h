/* The globe: outdoors (the town) the ground is drawn bent round a drum along X of radius
 * GLOBE_RADIUS, the map's Z running round it. A map distance of GLOBE_ARC_LENGTH along Z is
 * the turn GLOBE_ARC_ANGLE (a 16-bit fraction of a turn) round the drum, so arcs keep their map
 * length. Globe_Bend takes a map point into the drawn world (its Y the height above the drum)
 * and Globe_Unbend takes a drawn point back; indoors both copy the point.
 *
 * Far beyond the point the camera looks at, the ground also sinks (Globe_BendFar): the view
 * (data_021c749c, a C++ global object) keeps that point, its turn round the drum, the distance
 * beyond which the ground sinks (shorter the lower the camera's pitch) and how fast it sinks. */
#ifndef CLEAN_MAIN_GLOBE_H
#define CLEAN_MAIN_GLOBE_H

#include "autoload_2/vector.h"
#include "types.h"

#define GLOBE_RADIUS 0x1f576        /* about 31.3 */
#define GLOBE_ARC_ANGLE 0x2999      /* the turn whose arc is GLOBE_ARC_LENGTH */
#define GLOBE_ARC_LENGTH 0x20000    /* 32.0: the value of data_021c748c */
#define GLOBE_CIRCUMFERENCE 0xc4ec6 /* 2 pi GLOBE_RADIUS */

/* The point the camera looks at, as the far ground's sinking sees it (data_021c749c). */
typedef struct GlobeView {
    Vec3 point; /* 0x00: a map point */
    s16 angle;  /* 0x0c: its turn round the drum (0 indoors) */
    u8 pad_0e[2];
    fx32 sink_distance; /* 0x10: along -Z beyond the point, where the ground starts to sink */
    fx32 sink_slope;    /* 0x14: how much it sinks for each unit further */
} GlobeView;

void Globe_UpdateView(GlobeView *view, const Vec3 *point);
void Globe_DestructView(GlobeView *view);
GlobeView *Globe_ConstructView(GlobeView *view);
int Globe_Radius(void);
int Globe_ArcAngle(void);
int Globe_HorizonAngle(const Vec3 *point);
int Globe_Unbend(Vec3 *out, const Vec3 *in);
int Globe_Bend(Vec3 *out, const Vec3 *in);
int Globe_BendFar(Vec3 *out, const Vec3 *in);
int Globe_ArcLength(int angle);

#endif
