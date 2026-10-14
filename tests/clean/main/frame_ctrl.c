#include "../../../clean/main/frame_ctrl.h"
#include "diffcheck.h"

#define CTRL DIFF_SCRATCH
#define RAMP (DIFF_SCRATCH + 0x40)
/* where the caller leaves a fifth argument */
#define STACK_ARGS DIFF_STACK_ARGS

static FrameCtrl *ctrl_at(uint32_t address)
{
    return (FrameCtrl *) (uintptr_t) address;
}

/* Speeds the game uses (1, 2 and 4 frames a step) and slower or faster ones in between,
 * including 0 for a paused counter. */
static fx32 random_speed(DiffRng *rng)
{
    static const fx32 common[] = {0x1000, 0x2000, 0x4000, 0x800};
    if (diff_range(rng, 0, 1) == 0) {
        return common[diff_range(rng, 0, 3)];
    }
    return diff_range(rng, 0, 15) == 0 ? 0 : diff_range(rng, 1, 0x6000);
}

/* A position the counter can hold: anywhere in the sequence, often on a whole frame. */
static fx32 random_position(DiffRng *rng, fx32 end)
{
    fx32 at = diff_range(rng, 0, end - 1);
    return diff_range(rng, 0, 1) == 0 ? at & ~0xfff : at;
}

/* A counter as the game leaves it: after its start or after a step, which moves it by less than
 * one sequence length. */
static void a_counter(DiffRng *rng, uint32_t args[4])
{
    FrameCtrl *c = ctrl_at(CTRL);
    int frames = diff_range(rng, 0, 3) == 0 ? diff_range(rng, 1, 4) : diff_range(rng, 1, 300);
    c->vtable = (const void *) (uintptr_t) 0x020dd184u;
    c->end = frames << 12;
    c->speed = random_speed(rng);
    c->flags = (u8) diff_range(rng, 0, 3);
    c->previous = random_position(rng, c->end);
    switch (diff_range(rng, 0, 3)) {
        case 0:
            c->frame = c->previous; /* just started, or paused */
            break;
        case 1:
            c->frame = c->end - 0x1000; /* stopped on the last frame */
            break;
        default:
            c->frame = random_position(rng, c->end);
            break;
    }
    if (diff_range(rng, 0, 7) == 0) {
        c->frame = 0;
    }
    args[0] = CTRL;
    /* a frame in the sequence, sometimes the one the counter is on */
    switch (diff_range(rng, 0, 3)) {
        case 0:
            args[1] = (uint32_t) (c->frame >> 12);
            break;
        case 1:
            args[1] = (uint32_t) (c->previous >> 12);
            break;
        case 2:
            args[1] = (uint32_t) c->frame; /* small positions meet the unconverted compare */
            break;
        default:
            args[1] = (uint32_t) diff_range(rng, 0, frames);
            break;
    }
}

static uint32_t passed(const uint32_t args[4])
{
    return (uint32_t) FrameCtrl_Passed(ctrl_at(args[0]), (int) args[1]);
}

static uint32_t is_done(const uint32_t args[4])
{
    return (uint32_t) FrameCtrl_IsDone(ctrl_at(args[0]));
}

static uint32_t step(const uint32_t args[4])
{
    FrameCtrl_Step(ctrl_at(args[0]));
    return 0;
}

static void init_args(DiffRng *rng, uint32_t args[4])
{
    int frames = diff_range(rng, 0, 7) == 0 ? diff_range(rng, 0, 2) : diff_range(rng, 1, 300);
    args[0] = CTRL;
    args[1] = (uint32_t) frames;
    args[2] = (uint32_t) diff_range(rng, 0, 3);
    args[3] = (uint32_t) random_speed(rng);
    uint32_t start = diff_range(rng, 0, 2) == 0 ? 0xffff : (uint32_t) diff_range(rng, 0, frames > 0 ? frames - 1 : 0);
    *(uint32_t *) (uintptr_t) STACK_ARGS = start;
}

static uint32_t init(const uint32_t args[4])
{
    u16 *start = (u16 *) (uintptr_t) STACK_ARGS;
    FrameCtrl_Init(ctrl_at(args[0]), args[1], (u8) args[2], (fx32) args[3], *start);
    return 0;
}

/* A ramp at rest, or part way with the rate its start computes: 1.0 over 1-60 steps. */
static void a_ramp(DiffRng *rng, uint32_t args[4])
{
    Ramp *r = (Ramp *) (uintptr_t) RAMP;
    if (diff_range(rng, 0, 4) == 0) {
        r->rate = 0;
        r->weight = diff_range(rng, 0, 1) ? 0x1000 : 0;
    } else {
        int steps = diff_range(rng, 1, 60);
        r->rate = 0x1000 / steps;
        r->weight = r->rate * diff_range(rng, 0, steps);
    }
    args[0] = RAMP;
}

static uint32_t ramp_step(const uint32_t args[4])
{
    return (uint32_t) Ramp_Step((Ramp *) (uintptr_t) args[0]);
}

DIFF_CHECK(func_02056fcc, "main", 0x02056fcc | 1, 0, 0, init_args, init)
DIFF_CHECK(func_02056f28, "main", 0x02056f28 | 1, 32, 0, a_counter, passed)
DIFF_CHECK(func_02056f94, "main", 0x02056f94 | 1, 32, 0, a_counter, is_done)
DIFF_CHECK(func_02056ffc, "main", 0x02056ffc | 1, 0, 0, a_counter, step)
DIFF_CHECK(func_02056e84, "main", 0x02056e84 | 1, 32, 0, a_ramp, ramp_step)
