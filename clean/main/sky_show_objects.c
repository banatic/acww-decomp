/* The objects of the show (sky_show_objects.h). */
#include "sky_show_objects.h"

#include "cell_anim.h"
#include "clean.h"
#include "sky_resources.h"
#include "sky_show.h"
#include "main_random.h"
#include "scene_lights.h"

static_assert(sizeof(SkyShowObjectVars) == 0x14, "the words at 0x60");
static_assert(sizeof(SkyShowColors) == 4, "a place's colours");

#define SKY_SHOW_OBJECT_PRIORITY 2
#define SKY_SHOW_OBJECT_TOP 0xc0000       /* y 192: the bottom of the screen */
#define SKY_SHOW_OBJECT_START_Y 0xbf000   /* y 191: where a shell starts */
#define SKY_SHOW_OBJECT_STRETCH 0x20000   /* a shell is stretched for its first 8 pixels */
#define SKY_SHOW_OBJECT_GROW 0x14cd       /* its height grows by this each frame at the top */
#define SKY_SHOW_OBJECT_GROWN 0xa000      /* until 10.0, when it is hidden */
#define SKY_SHOW_OBJECT_BURST_WAIT 6      /* frames hidden, plus one, before it bursts */
#define SKY_SHOW_OBJECT_BURST_DROP 0x2000 /* the burst is 2 pixels above the shell's height */
#define SKY_SHOW_OBJECT_SHELL_SOUND 0x802
#define SKY_SHOW_OBJECT_BURST_SOUND 0x803
#define SKY_SHOW_OBJECT_LARGE_SOUND 0x804
#define SKY_SHOW_OBJECT_LARGE_SOURCE 1 /* the sound source of a large one; a place's: 2 + place */
#define SKY_SHOW_OBJECT_LARGE_RADIUS 4
#define SKY_SHOW_OBJECT_MARK_FRAME 0x1d /* the frame a burst sets data_020d2eec's bit */
#define SKY_SHOW_OBJECT_FADE_START 0x10 /* a burst's colours fade over frames 16 to 26 */
#define SKY_SHOW_OBJECT_FADE_END 0x1b
#define SKY_SHOW_OBJECT_FLICKER 0xb        /* and flicker from frame 11 */
#define SKY_SHOW_OBJECT_SMALL_FRAMES 0x24  /* the last entry of the tables of a burst's sizes */
#define SKY_SHOW_OBJECT_SECOND_FRAMES 0xb0 /* and of the second's */

extern SkyObjects data_021f8b48;
extern SkyPalettes data_021fba00;     /* the objects' palettes (0x2eb8 of the objects) */
extern SkyObjectSlot data_021fa678[]; /* the objects' slots */
extern const Vec3 data_021c67d0;      /* the point the camera looks at */
extern const fx32 data_020ca0ec;      /* an acre's width in world units */
extern const fx32 data_020ca0e8;      /* and depth */
extern const u32 data_020d2eec;       /* SKY_SHOW_PARAM_BIT29 */
extern const fx32 data_020d274c[];    /* sizes by the animation's frame: large, second */
extern const fx32 data_020d2444[];    /* large */
extern const fx32 data_020d27fc[];    /* second */
extern const fx32 data_020d2468[];    /* the others */
extern const fx32 data_020d22d0[2];   /* a burst's brightness: 1.0, 0.5 */
extern const SkyShowColors data_020d2344[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);

static SkyShowObjectVars *sky_show_object_vars(SkyObject *object)
{
    return (SkyShowObjectVars *) (void *) SkyObject_Body(object)->words;
}

/* Shells are the looks of animations 0x21, 0x24, 0x27 and 0x2a. */
static int sky_show_object_is_shell(s32 animation)
{
    u32 offset = (u32) animation - 0x21;
    return offset <= 9 && ((0x249u >> offset) & 1) != 0;
}

static int sky_show_object_large(u32 param)
{
    return (param & SKY_SHOW_PARAM_LARGE) != 0;
}

static int sky_show_object_place(u32 param)
{
    return (int) ((param & SKY_SHOW_PARAM_PLACE) >> 8);
}

/* func_020bfcd8: an object of the show taken down; a burst that sets colours clears them. */
void SkyShowObject_TakeDown(SkyObject *object)
{
    if (!sky_show_object_is_shell(SkyObject_Body(object)->animation) &&
        (sky_show_object_vars(object)->param & SKY_SHOW_PARAM_SECOND) == 0) {
        SkyShowObject_ClearColors(object);
    }
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020bfcd8, SkyShowObject_TakeDown)

/* func_020bfd1c: a frame of a shell. While shown it rises 4 pixels a frame from the bottom of
 * the screen, stretched (its height 16.0 over the distance) for the first 8 pixels; once at
 * its height (position.z) it stays there and grows until hidden. 7 frames after it is hidden
 * it is done and adds the two objects of its burst. */
void SkyShowObject_ShellRun(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyShowObjectVars *vars = sky_show_object_vars(object);
    u32 param = vars->param;
    int large = sky_show_object_large(param);
    int burst = 0;
    if (body->hidden) {
        vars->wait++;
        if (vars->wait > SKY_SHOW_OBJECT_BURST_WAIT) {
            burst = 1;
        }
    } else {
        fx32 top = SKY_SHOW_OBJECT_TOP - body->position.z;
        fx32 risen = SkyShowObject_RiseDistance(top, vars->timer);
        if (risen <= SKY_SHOW_OBJECT_STRETCH) {
            body->scale_y = FX_Div(SKY_SHOW_OBJECT_STRETCH, risen);
            vars->base_y = SKY_SHOW_OBJECT_TOP - risen / 2;
        } else {
            if (risen < top) {
                body->scale_y = 0x1000;
            } else {
                body->scale_y = FX_MulFunc(body->scale_y, SKY_SHOW_OBJECT_GROW);
                if (body->scale_y >= SKY_SHOW_OBJECT_GROWN) {
                    body->scale_y = SKY_SHOW_OBJECT_GROWN;
                    body->hidden = 1;
                }
                risen = top;
            }
            vars->base_y = SKY_SHOW_OBJECT_TOP - (risen - FX_Div(0x10000, body->scale_y));
        }
        SkyShowObject_PlaceShifted(&body->position, vars->base_x, vars->base_y, large);
    }
    if (!burst) {
        return;
    }
    body->state = SKY_OBJECT_DONE;
    u32 place = (param & SKY_SHOW_PARAM_PLACE);
    u32 first;
    u32 second;
    if (sky_show_object_large(vars->param)) {
        first = place | SKY_SHOW_PARAM_LARGE;
        second = place | SKY_SHOW_PARAM_LARGE | SKY_SHOW_PARAM_SECOND | 1;
    } else {
        s32 animation = body->animation;
        first = place | ((u32) (animation - 2 - SKY_SHOW_OBJECT_ANIMATION_FIRST) & SKY_SHOW_PARAM_LOOK);
        second =
            place | ((u32) (animation - 1 - SKY_SHOW_OBJECT_ANIMATION_FIRST) & SKY_SHOW_PARAM_LOOK) | SKY_SHOW_PARAM_SECOND;
    }
    Vec3 at = {vars->base_x, body->position.z - SKY_SHOW_OBJECT_BURST_DROP, 0};
    SkyObjects_Add(&data_021f8b48, SKY_OBJECT_SHOW, SKY_ENTRY_ANY, &at, (int) first);
    SkyObjects_Add(&data_021f8b48, SKY_OBJECT_SHOW, SKY_ENTRY_ANY, &at, (int) second);
}
CLEAN_AS(func_020bfd1c, SkyShowObject_ShellRun)

/* func_020bfe6c: a frame of a burst: done once its animation is (clearing the colours it set);
 * until then sized by its frame, placed, and its colours set. At frame 29 it gets bit 29. */
void SkyShowObject_BurstRun(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyShowObjectVars *vars = sky_show_object_vars(object);
    u32 param = vars->param;
    int colors = (param & SKY_SHOW_PARAM_SECOND) == 0;
    int large = sky_show_object_large(param);
    if (CellAnim_IsDone(&body->anim)) {
        if (colors) {
            SkyShowObject_ClearColors(object);
        }
        body->state = SKY_OBJECT_DONE;
    } else {
        SkyShowObject_SetScale(object, -1);
        SkyShowObject_PlaceShifted(&body->position, vars->base_x, vars->base_y, large);
        if (colors) {
            SkyShowObject_SetColors(object);
        }
    }
    if (vars->timer == SKY_SHOW_OBJECT_MARK_FRAME) {
        vars->param |= data_020d2eec;
    }
}
CLEAN_AS(func_020bfe6c, SkyShowObject_BurstRun)

/* func_020bfee4: a frame of an object of the show, counted. */
void SkyShowObject_Run(SkyObject *object)
{
    sky_show_object_vars(object)->timer++;
    if (sky_show_object_is_shell(SkyObject_Body(object)->animation)) {
        SkyShowObject_ShellRun(object);
    } else {
        SkyShowObject_BurstRun(object);
    }
}
CLEAN_AS(func_020bfee4, SkyShowObject_Run)

/* func_020bff20: a shell set up: below the screen at a random x (large: 80 to 175, rising to
 * a height of 82 to 113, or just 82 when marked; others: 48 to 207, rising to 50 to 145),
 * moving up, stretched, and its sound played (0x802, from its place's source). */
void SkyShowObject_ShellSetUp(SkyObject *object, u32 param)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyShowObjectVars *vars = sky_show_object_vars(object);
    int large = (param & SKY_SHOW_PARAM_LARGE) != 0;
    u32 x;
    u32 height;
    if (large) {
        x = MainRandom_Below(0x60) + 0x50;
        height = ((param & SKY_SHOW_PARAM_MARKED) != 0 ? 0 : MainRandom_Below(0x20)) + 0x52;
    } else {
        x = MainRandom_Below(0xa0) + 0x30;
        height = MainRandom_Below(0x60) + 0x32;
    }
    vars->base_x = (fx32) (x << 12);
    vars->base_y = SKY_SHOW_OBJECT_START_Y;
    body->position.z = (fx32) (height << 12);
    SkyShowObject_PlaceShifted(&body->position, vars->base_x, vars->base_y, large);
    body->velocity.x = 0;
    body->velocity.y = -0x3800;
    body->velocity.z = 0;
    body->scale_y = SKY_SHOW_OBJECT_GROWN;
    int source = large ? SKY_SHOW_OBJECT_LARGE_SOURCE : sky_show_object_place(param) + 2;
    SkyObjectKinds_PlayHeldAt(object, source, SKY_SHOW_OBJECT_SHELL_SOUND);
}
CLEAN_AS(func_020bff20, SkyShowObject_ShellSetUp)

/* func_020bffc4: a burst set up where it was added: sized for frame 0, placed, its sound
 * played (0x803, a large one's 0x804) and its number handed to func_02065268 (a place's 1 to
 * 4, a large one's 5 to 8); a large one gets a radius of 4. */
void SkyShowObject_BurstSetUp(SkyObject *object, u32 param)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyShowObjectVars *vars = sky_show_object_vars(object);
    int large = (param & SKY_SHOW_PARAM_LARGE) != 0;
    SkyShowObject_SetScale(object, 0);
    vars->base_x = body->position.x;
    vars->base_y = body->position.y;
    SkyShowObject_PlaceShifted(&body->position, vars->base_x, vars->base_y, large);
    int sound = large ? SKY_SHOW_OBJECT_LARGE_SOUND : SKY_SHOW_OBJECT_BURST_SOUND;
    int place = sky_show_object_place(param);
    SkyObjectKinds_PlayHeldAt(object, large ? SKY_SHOW_OBJECT_LARGE_SOURCE : place + 2, sound);
    if (large) {
        body->radius = SKY_SHOW_OBJECT_LARGE_RADIUS;
        SceneLights_StartFlash(place + 5);
    } else {
        SceneLights_StartFlash(place + 1);
    }
}
CLEAN_AS(func_020bffc4, SkyShowObject_BurstSetUp)

/* func_020c003c: an object of the show set up by its look, as a shell or a burst. */
void SkyShowObject_SetUp(SkyObject *object, int param)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyShowObjectVars *vars = sky_show_object_vars(object);
    s32 animation = (param & (int) SKY_SHOW_PARAM_LOOK) + SKY_SHOW_OBJECT_ANIMATION_FIRST;
    body->animation = animation;
    body->priority = SKY_SHOW_OBJECT_PRIORITY;
    vars->param = (u32) param;
    vars->timer = 0;
    vars->wait = 0;
    if (sky_show_object_is_shell(animation)) {
        SkyShowObject_ShellSetUp(object, (u32) param);
    } else {
        SkyShowObject_BurstSetUp(object, (u32) param);
    }
}
CLEAN_AS(func_020c003c, SkyShowObject_SetUp)

/* func_020c0084: a burst's size for a frame of its animation (below 0: the frame it shows),
 * from the table for its kind, the frame kept within the table (0 to 36, the second's 0 to
 * 176). */
void SkyShowObject_SetScale(SkyObject *object, int frame)
{
    SkyObjectBody *body = SkyObject_Body(object);
    u32 param = sky_show_object_vars(object)->param;
    int second = (param & SKY_SHOW_PARAM_SECOND) != 0;
    const fx32 *sizes;
    int last;
    if (sky_show_object_large(param)) {
        sizes = second ? data_020d274c : data_020d2444;
        last = second ? SKY_SHOW_OBJECT_SECOND_FRAMES : SKY_SHOW_OBJECT_SMALL_FRAMES;
    } else {
        sizes = second ? data_020d27fc : data_020d2468;
        last = second ? SKY_SHOW_OBJECT_SECOND_FRAMES : SKY_SHOW_OBJECT_SMALL_FRAMES;
    }
    if (frame < 0) {
        frame = CellAnim_Frame(&body->anim);
    }
    int index;
    if (frame < 0) {
        index = 0;
    } else if (frame <= last) {
        index = frame;
    } else {
        index = last;
    }
    fx32 size = sizes[index];
    body->scale_x = size;
    body->scale_y = size;
}
CLEAN_AS(func_020c0084, SkyShowObject_SetScale)

/* func_020c00f8: how far a shell has risen after `frames`: 4 pixels a frame. */
fx32 SkyShowObject_RiseDistance(fx32 unused, int frames)
{
    (void) unused;
    return (fx32) ((u32) frames << 14);
}
CLEAN_AS(func_020c00f8, SkyShowObject_RiseDistance)

/* func_020c00fc: the two colours a burst sets, cleared. */
void SkyShowObject_ClearColors(SkyObject *object)
{
    u32 param = sky_show_object_vars(object)->param;
    int first = SkyShowObject_ColorIndex(sky_show_object_place(param), sky_show_object_large(param));
    int second = first + 1;
    if (first < SKY_SHOW_OBJECT_NO_COLOR) {
        SkyPalettes_ClearOverride(&data_021fba00, first);
    }
    if (second < SKY_SHOW_OBJECT_NO_COLOR) {
        SkyPalettes_ClearOverride(&data_021fba00, second);
    }
}
CLEAN_AS(func_020c00fc, SkyShowObject_ClearColors)

/* A 5-bit component of a colour as a fixed-point number. */
static fx32 sky_show_object_component(u16 color, int shift)
{
    return (fx32) (((u32) (color >> shift) & 0x1f) << 12);
}

/* A component rounded to a whole number, at most 31. */
static u32 sky_show_object_round(fx32 value)
{
    u32 rounded = (u32) ((value + 0x800) >> 12);
    return rounded > 0x1f ? 0x1f : rounded;
}

/* func_020c013c: a burst's two colours set: its place's colour, faded from the first to the
 * second over frames 16 to 26, the first at full brightness and the second at half, then from
 * frame 11 the two brightnesses swapped every two frames; its slot's resource reloaded.
 * QUIRK: a component below 0 after rounding becomes 31, like one above. */
void SkyShowObject_SetColors(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    SkyShowObjectVars *vars = sky_show_object_vars(object);
    int frames = vars->timer;
    fx32 t;
    if (frames < SKY_SHOW_OBJECT_FADE_START) {
        t = 0;
    } else if (frames < SKY_SHOW_OBJECT_FADE_END) {
        t = ((frames - SKY_SHOW_OBJECT_FADE_START) << 12) / (SKY_SHOW_OBJECT_FADE_END - SKY_SHOW_OBJECT_FADE_START);
    } else {
        t = 0x1000;
    }
    u32 param = vars->param;
    int place = sky_show_object_place(param);
    int first = SkyShowObject_ColorIndex(place, sky_show_object_large(param));
    int second = first + 1;
    int dim_first = 0;
    int dim_second = 0;
    if (frames >= SKY_SHOW_OBJECT_FLICKER) {
        dim_first = (frames & 2) == 0;
        dim_second = (frames & 2) != 0;
    }
    fx32 bright_first = data_020d22d0[dim_first];
    fx32 bright_second = data_020d22d0[dim_second];
    if (place >= SKY_SHOW_PLACES || first >= SKY_SHOW_OBJECT_NO_COLOR || second >= SKY_SHOW_OBJECT_NO_COLOR) {
        return;
    }
    const SkyShowColors *colors = &data_020d2344[place];
    fx32 rest = 0x1000 - t;
    fx32 red = FX_MulFunc(sky_show_object_component(colors->from, 0), rest);
    red += FX_MulFunc(sky_show_object_component(colors->to, 0), t);
    fx32 green = FX_MulFunc(sky_show_object_component(colors->from, 5), rest);
    green += FX_MulFunc(sky_show_object_component(colors->to, 5), t);
    fx32 blue = FX_MulFunc(sky_show_object_component(colors->from, 10), rest);
    blue += FX_MulFunc(sky_show_object_component(colors->to, 10), t);
    fx32 red_first = FX_MulFunc(red, bright_first);
    fx32 green_first = FX_MulFunc(green, bright_first);
    fx32 blue_first = FX_MulFunc(blue, bright_first);
    fx32 red_second = FX_MulFunc(red, bright_second);
    fx32 green_second = FX_MulFunc(green, bright_second);
    fx32 blue_second = FX_MulFunc(blue, bright_second);
    u16 out[2];
    out[0] = (u16) (sky_show_object_round(red_first) | (sky_show_object_round(green_first) << 5) |
                    (sky_show_object_round(blue_first) << 10));
    out[1] = (u16) (sky_show_object_round(red_second) | (sky_show_object_round(green_second) << 5) |
                    (sky_show_object_round(blue_second) << 10));
    int slot = body->slot;
    int resource = body->resource;
    SkyPalettes_SetOverride(&data_021fba00, first, &out[0]);
    SkyPalettes_SetOverride(&data_021fba00, second, &out[1]);
    SkySlot_Reload((SkyObjectSlot *) ((uintptr_t) data_021fa678 + (u32) slot * (u32) sizeof(SkyObjectSlot)), resource);
}
CLEAN_AS(func_020c013c, SkyShowObject_SetColors)

/* func_020c0324: an object of the show placed at (x, y) shifted by the camera: to the side
 * against how far the point the camera looks at is east of the middle of the town's six acres
 * (16 pixels at two acres or more), and down by up to 16 pixels the farther north of the
 * town's first acre row it looks (eased over four acres' depth), the more the higher the
 * object is on the screen (none at line 191). The shift is up instead while the camera looks
 * less than about 1.2 acres' depth north of that row. */
void SkyShowObject_PlaceShifted(Vec3 *position, fx32 x, fx32 y, int large)
{
    (void) large;
    fx32 depth = data_020ca0e8;
    fx32 north = data_021c67d0.z - depth;
    fx32 width = data_020ca0ec;
    fx32 half_span = width * 4 / 2;
    fx32 side = FX_Div((fx32) ((u32) (data_021c67d0.x - width * 3) << 4), half_span);
    fx32 away = FX_Div(north, (fx32) ((u32) depth << 2));
    if (side < -0x10000) {
        side = -0x10000;
    } else if (side > 0x10000) {
        side = 0x10000;
    }
    if (away < 0) {
        away = 0;
    } else if (away > 0x1000) {
        away = 0x1000;
    }
    away -= 0x1000;
    away = FX_MulFunc(away, away);
    away = 0x1000 - away;
    side = -side;
    fx32 drop = (fx32) ((u32) (away - 0x800) << 5);
    fx32 line;
    if (y < 0) {
        line = 0;
    } else if (y > SKY_SHOW_OBJECT_START_Y) {
        line = SKY_SHOW_OBJECT_START_Y;
    } else {
        line = y;
    }
    line = FX_Div(SKY_SHOW_OBJECT_START_Y - line, SKY_SHOW_OBJECT_START_Y);
    drop = FX_MulFunc(drop, line);
    position->x = x + side;
    position->y = y + drop;
}
CLEAN_AS(func_020c0324, SkyShowObject_PlaceShifted)

/* func_020c03f4: the first of the two overridable colours of a burst: a large one's 0, a
 * place's 2, 4, 6 or 8, else none (15). */
int SkyShowObject_ColorIndex(int place, int large)
{
    if (large) {
        return 0;
    }
    switch (place) {
        case 0:
            return 2;
        case 1:
            return 4;
        case 2:
            return 6;
        case 3:
            return 8;
        default:
            return SKY_SHOW_OBJECT_NO_COLOR;
    }
}
CLEAN_AS(func_020c03f4, SkyShowObject_ColorIndex)
