/* The ground drawn bent round a drum outdoors (globe.h). */
#include "globe.h"

#include "autoload_2/fx_math.h"
#include "camera_control.h"
#include "camera_view.h"
#include "clean.h"

static_assert(offsetof(GlobeView, angle) == 0x0c, "GlobeView layout");
static_assert(offsetof(GlobeView, sink_distance) == 0x10, "GlobeView layout");
static_assert(offsetof(GlobeView, sink_slope) == 0x14, "GlobeView layout");

/* The running scene (data_021f6948): its byte 4 is 1 outdoors. */
typedef struct GlobeScene {
    u8 unk_00[4];
    u8 outdoors;
} GlobeScene;
extern GlobeScene *data_021f6948;

/* The camera, while it exists. */
extern CameraControl *data_021c67a4;
/* The map distance whose arc is GLOBE_ARC_ANGLE (GLOBE_ARC_LENGTH, set at start-up). */
extern fx32 data_021c748c;
/* The view of the camera's point (globe.h). */
extern GlobeView data_021c749c;

/* Sine and cosine of each of 4096 angles, interleaved (NitroSDK's table). */
extern const fx16 FX_SinCosTable_[4096 * 2];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_Sqrt(fx32 x);

/* The camera's pitches between which the sinking distance changes, and that distance at
 * each. */
#define GLOBE_PITCH_HIGH 0x27f7
#define GLOBE_PITCH_LOW 0x21fd
#define GLOBE_SINK_DISTANCE_HIGH 0xe000 /* 14.0 */
#define GLOBE_SINK_DISTANCE_LOW 0xb400  /* 11.25 */

static int outdoors(void)
{
    return data_021f6948->outdoors == 1;
}

/* The turn round the drum of the map distance `z` along Z.
 * QUIRK: the product is taken to 32 bits and its bits 12-27 kept as a signed 16-bit angle. */
static s16 turn_of(fx32 z)
{
    return (s16) (((u32) FX_Div(z, data_021c748c) * GLOBE_ARC_ANGLE) >> 12);
}

/* `in` copied to `out` a coordinate at a time, in this order. */
static void copy_point(Vec3 *out, const Vec3 *in)
{
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
}

/* `out`'s Y and Z: `distance` from the drum's axis at `angle`. */
static void place_on_drum(Vec3 *out, fx32 distance, s16 angle)
{
    int index = (u16) angle >> 4;

    out->y = FX_MulFunc(distance, FX_SinCosTable_[index * 2 + 1]);
    out->z = FX_MulFunc(distance, FX_SinCosTable_[index * 2]);
}

/* func_0203f684 (each frame, from the camera's process, with the point it looks at): the view
 * keeps the point; with a camera, the sinking distance from its pitch (kept within
 * GLOBE_PITCH_LOW..HIGH: GLOBE_SINK_DISTANCE_HIGH at the high one down to ..._LOW at the low
 * one); outdoors the point's turn round the drum, else 0. */
void Globe_UpdateView(GlobeView *view, const Vec3 *point)
{
    copy_point(&view->point, point);

    CameraControl *camera = data_021c67a4;
    if (camera != NULL) {
        int pitch = CameraControl_Pitch(camera);
        if (pitch > GLOBE_PITCH_HIGH) {
            pitch = GLOBE_PITCH_HIGH;
        } else if (pitch < GLOBE_PITCH_LOW) {
            pitch = GLOBE_PITCH_LOW;
        }
        /* 0 at the high pitch, 1.0 at the low one. */
        fx32 share = FX_Div((pitch - GLOBE_PITCH_HIGH) * 0x1000, (GLOBE_PITCH_LOW - GLOBE_PITCH_HIGH) * 0x1000);
        view->sink_distance = FX_MulFunc(GLOBE_SINK_DISTANCE_LOW - GLOBE_SINK_DISTANCE_HIGH, share) + GLOBE_SINK_DISTANCE_HIGH;
    }

    if (outdoors()) {
        view->angle = turn_of(view->point.z);
    } else {
        view->angle = 0;
    }
}
CLEAN_AS(func_0203f684, Globe_UpdateView)

/* func_0203f724: the view's destructor. */
void Globe_DestructView(GlobeView *view)
{
    (void) view;
}
CLEAN_AS(func_0203f724, Globe_DestructView)

/* func_0203f728: the view's constructor: the origin, no turn, the ground sinking 1 for each 10
 * units from 14.0 on. */
GlobeView *Globe_ConstructView(GlobeView *view)
{
    view->point.x = 0;
    view->point.y = 0;
    view->point.z = 0;
    view->angle = 0;
    view->sink_slope = FX_Div(0x1000, 0xa000);
    view->sink_distance = GLOBE_SINK_DISTANCE_HIGH;
    return view;
}
CLEAN_AS(func_0203f728, Globe_ConstructView)

/* func_0203f758 */
int Globe_Radius(void)
{
    return GLOBE_RADIUS;
}
CLEAN_AS(func_0203f758, Globe_Radius)

/* func_0203f760 */
int Globe_ArcAngle(void)
{
    return GLOBE_ARC_ANGLE;
}
CLEAN_AS(func_0203f760, Globe_ArcAngle)

/* func_0203f768: outdoors, the angle of the horizon seen from the drawn `point`: the point's
 * own angle round the drum less the angle between it and where its tangent touches the drum
 * (kept to 16 bits); 0 indoors. */
int Globe_HorizonAngle(const Vec3 *point)
{
    if (!outdoors()) {
        return 0;
    }
    fx32 z_squared = FX_MulFunc(point->z, point->z);
    fx32 y_squared = FX_MulFunc(point->y, point->y);
    fx32 radius_squared = FX_MulFunc(GLOBE_RADIUS, GLOBE_RADIUS);
    fx32 tangent = FX_Sqrt(y_squared + z_squared - radius_squared);
    int angle = Math_Atan2(point->z, point->y);
    int touch = Math_Atan2(tangent, GLOBE_RADIUS);
    return (s16) (angle - touch);
}
CLEAN_AS(func_0203f768, Globe_HorizonAngle)

/* func_0203f7d0: outdoors, the drawn point `in` taken back to the map: X kept, Y its height
 * above the drum and Z the length of its arc; its angle round the drum. Indoors a copy, 0. */
int Globe_Unbend(Vec3 *out, const Vec3 *in)
{
    if (!outdoors()) {
        copy_point(out, in);
        return 0;
    }
    int angle = Math_Atan2(in->z, in->y);
    out->x = in->x;
    fx32 z_squared = FX_MulFunc(in->z, in->z);
    fx32 y_squared = FX_MulFunc(in->y, in->y);
    out->y = FX_Sqrt(y_squared + z_squared) - GLOBE_RADIUS;
    out->z = Globe_ArcLength(angle);
    return angle;
}
CLEAN_AS(func_0203f7d0, Globe_Unbend)

/* func_0203f844: outdoors, the map point `in` bent onto the drum: X kept, its height laid off
 * from the drum at its Z's turn; that turn. Indoors a copy, 0. */
int Globe_Bend(Vec3 *out, const Vec3 *in)
{
    if (!outdoors()) {
        copy_point(out, in);
        return 0;
    }
    fx32 distance = in->y + GLOBE_RADIUS;
    s16 angle = turn_of(in->z);
    out->x = in->x;
    place_on_drum(out, distance, angle);
    return angle;
}
CLEAN_AS(func_0203f844, Globe_Bend)

/* func_0203f8d0: as Globe_Bend, but a point further along -Z than the view's sinking distance
 * beyond the camera's point sinks by the view's slope for each unit past it. */
int Globe_BendFar(Vec3 *out, const Vec3 *in)
{
    if (!outdoors()) {
        copy_point(out, in);
        return 0;
    }
    fx32 distance = in->y + GLOBE_RADIUS;
    const GlobeView *view = &data_021c749c;
    if (in->z <= view->point.z - view->sink_distance) {
        fx32 past = in->z - (view->point.z - view->sink_distance);
        if (past < 0) {
            past = -past;
        }
        distance -= FX_MulFunc(view->sink_slope, past);
    }
    s16 angle = turn_of(in->z);
    out->x = in->x;
    place_on_drum(out, distance, angle);
    return angle;
}
CLEAN_AS(func_0203f8d0, Globe_BendFar)

/* func_0203f984: the length of the drum's arc of `angle` (its low 16 bits, as a turn from 0 to
 * nearly 1), rounded. */
int Globe_ArcLength(int angle)
{
    fx32 share = FX_Div((angle & 0xffff) << 12, 0x10000000);
    return (int) (((s64) share * GLOBE_CIRCUMFERENCE + 0x800) >> 12);
}
CLEAN_AS(func_0203f984, Globe_ArcLength)
